Info<< "Reading thermophysical properties\n" << endl;

Info<< "Reading field T\n" << endl;
volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field p_rgh\n" << endl;
volScalarField p_rgh
(
    IOobject
    (
        "p_rgh",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

#include "readTransportProperties.H"

//Calculating phase-fraction gamma_L
Info<< "Calculating volume fraction gamma_L\n" << endl;
volScalarField gamma_L
(
    IOobject
    (
        "gamma_L",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    max(min((T-T_L)/T_L,scalar(1)),scalar(0))
);
gamma_L.write();

volScalarField Tcons("Tcons", (T_L-T_S)*gamma_L + T_S);

volScalarField k
(
    IOobject
    (
        "k",
        runTime.timeName(),
        mesh
    ),
    gamma_L*(k_La+k_Lb*(T-TRef_k_L)+k_Lc*pow(T-TRef_k_L,2))
            + (scalar(1) - gamma_L)*(k_Sa+k_Sb*(T-TRef_k_S)+k_Sc*pow(T-TRef_k_S,2))
);

volScalarField cp
(
    IOobject
    (
        "cp",
        runTime.timeName(),
        mesh
    ),
    gamma_L*cp_L+ (scalar(1) - gamma_L)*cp_S
);
cp.oldTime();

volScalarField rhomix
(
    IOobject
    (
        "rhomix",
        runTime.timeName(),
        mesh
    ),
    gamma_L*(rho_La
            +rho_Lb*max(T-TRef_rho_L,TRef_rho_L*scalar(0))
            +rho_Lc*pow(max(T-TRef_rho_L,TRef_rho_L*scalar(0)),2)
            +rho_Ld*pow(max(T-TRef_rho_L,TRef_rho_L*scalar(0)),2.5)
            +rho_Le*pow(max(T-TRef_rho_L,TRef_rho_L*scalar(0)),3))
    +(scalar(1)-gamma_L)*(rho_Sa
                          +rho_Sb*(T-TRef_rho_L)
                          +rho_Sc*pow(T-TRef_rho_L,2))
);

volScalarField nu
(
    IOobject
    (
        "nu",
        runTime.timeName(),
        mesh
    ),
    1/(nua+nub*T+nuc*pow(T,2))
);

volScalarField rhomixCp
(
    IOobject
    (
        "rhomix*cp",
        runTime.timeName(),
        mesh
    ),
    rhomix*cp
);

surfaceScalarField rhomixPhiCp
(
    IOobject
    (
        "rhomix*phi*cp",
        runTime.timeName(),
        mesh
    ),
    phi*fvc::interpolate(cp)*fvc::interpolate(rhomix)
);

surfaceScalarField rhomixPhi
(
    IOobject
    (
        "rhomix*phi",
        runTime.timeName(),
        mesh
    ),
    phi*fvc::interpolate(rhomix)
);

// Kinematic density for buoyancy force
volScalarField rhok
(
    IOobject
    (
        "rhok",
        runTime.timeName(),
        mesh
    ),
    1.0 - beta*(T - TRef)
);

volScalarField DarcyTerm
(
    IOobject
    (
        "DarcyTerm",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    DarcyConstant*pow(scalar(1)-gamma_L,2)/(pow(gamma_L,3)+DarcyTerm_epsilon)
);
//DarcyTerm.write();

#include "readGravitationalAcceleration.H"
#include "readhRef.H"
#include "gh.H"


volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    p_rgh + rhok*gh
);

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell
(
    p,
    p_rgh,
    pimple.dict(),
    pRefCell,
    pRefValue
);

if (p_rgh.needReference())
{
    p += dimensionedScalar
    (
        "p",
        p.dimensions(),
        pRefValue - getRefCellValue(p, pRefCell)
    );
}

mesh.setFluxRequired(p_rgh.name());

#include "createMRF.H"
