IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

singlePhaseTransportModel laminarTransport(U, phi);

// Thermal expansion coefficient [1/K]
dimensionedScalar beta
(
    "beta",
    dimless/dimTemperature,
    laminarTransport
);

// Reading density rho
dimensionedScalar rho(transportProperties.lookup("rho"));

// Reading specific heat capacity
dimensionedScalar cp_S(transportProperties.lookup("cp_S"));
dimensionedScalar cp_L(transportProperties.lookup("cp_L"));

// Reading thermal conductivity
dimensionedScalar k_S(transportProperties.lookup("k_S"));
dimensionedScalar k_L(transportProperties.lookup("k_L"));

// Latent heat of melting
dimensionedScalar h_m(transportProperties.lookup("h_m"));

// Solidus and liquidus temperatures
dimensionedScalar T_S(transportProperties.lookup("T_S"));
dimensionedScalar T_L(transportProperties.lookup("T_L"));

// Calculate melting temperature
dimensionedScalar T_m
(
    "T_m",
    (T_L+T_S)/scalar(2.0)
);

// Reading parameters for Darcy source term
dimensionedScalar DarcyConstant(transportProperties.lookup("DarcyConstant"));
dimensionedScalar DarcyTerm_epsilon(transportProperties.lookup("DarcyTerm_epsilon"));

// Reading kinematic viscosity
dimensionedScalar TRef_nu(transportProperties.lookup("TRef_nu"));
dimensionedScalar nua(transportProperties.lookup("nua"));
dimensionedScalar nub(transportProperties.lookup("nub"));
dimensionedScalar nuc(transportProperties.lookup("nuc"));

// Reading liquid density
dimensionedScalar TRef_rho_L(transportProperties.lookup("TRef_rho_L"));
dimensionedScalar rho_La(transportProperties.lookup("rho_La"));
dimensionedScalar rho_Lb(transportProperties.lookup("rho_Lb"));
dimensionedScalar rho_Lc(transportProperties.lookup("rho_Lc"));
dimensionedScalar rho_Ld(transportProperties.lookup("rho_Ld"));
dimensionedScalar rho_Le(transportProperties.lookup("rho_Le"));

// Reading solid density
dimensionedScalar TRef_rho_S(transportProperties.lookup("TRef_rho_S"));
dimensionedScalar rho_Sa(transportProperties.lookup("rho_Sa"));
dimensionedScalar rho_Sb(transportProperties.lookup("rho_Sb"));
dimensionedScalar rho_Sc(transportProperties.lookup("rho_Sc"));

// Reference temperature [K]
dimensionedScalar TRef("TRef", dimTemperature, laminarTransport);
