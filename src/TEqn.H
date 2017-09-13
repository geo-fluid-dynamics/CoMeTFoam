{

    int iter = 0;
    int minTiter = 2;
    int maxTiter = 100;
    float gamma_L_Tol = 1e-6;
    scalar relaxGamma = 0.7;

    scalar residual = 1;

    do
    {
        iter++;
        gamma_L.storePrevIter();

        // mixture specific heat
        cp = cp_L*gamma_L + cp_S*(scalar(1) - gamma_L);

        // mixture specific heat times mass flux
        phiCp = fvc::interpolate(cp)*phi;

        // mixture thermal conductivity
        k = k_L*gamma_L + k_S*(scalar(1) - gamma_L);

        fvScalarMatrix TEqn
        (
            fvm::ddt(cp,T)
          + fvm::div(phiCp, T)
          + h_m*fvc::ddt(gamma_L)
          + h_m*fvc::div(phi, gamma_L)
          - T_m*fvc::ddt(cp)
          - T_m*fvc::div(phiCp)
          - fvm::laplacian(k/rho, T)
        );

        TEqn.relax();

        TEqn.solve();

        //rhok = 1.0 - beta*(T - TRef);

        Tcons = (T_L-T_S)*gamma_L+T_S;
        gamma_L = max(min(gamma_L + relaxGamma*cp/h_m*(T - Tcons),scalar(1)),scalar(0));

        residual = gMax(mag(gamma_L.primitiveField() - gamma_L.prevIter().primitiveField()));

        Info << "Correcting gamma_L, max residual = " << residual
        << endl;

    }while ((iter < minTiter || residual > gamma_L_Tol ) && iter <= maxTiter);

    // rhok (parabolic density profile) for pure water
    rhok = 1/999.845079*(999.845079+0.06378*max(beta*(T-T_m),scalar(0))-0.0080125*max(beta*(T-T_m),scalar(0))*max(beta*(T-T_m),scalar(0)));

    DarcyTerm = DarcyConstant*pow(scalar(1)-gamma_L,2)/(pow(gamma_L,3)+DarcyTerm_epsilon);

}
