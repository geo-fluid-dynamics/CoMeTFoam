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
dimensionedScalar nua(transportProperties.lookup("nua"));
dimensionedScalar nub(transportProperties.lookup("nub"));
dimensionedScalar nuc(transportProperties.lookup("nuc"));


// Reference temperature [K]
dimensionedScalar TRef("TRef", dimTemperature, laminarTransport);
