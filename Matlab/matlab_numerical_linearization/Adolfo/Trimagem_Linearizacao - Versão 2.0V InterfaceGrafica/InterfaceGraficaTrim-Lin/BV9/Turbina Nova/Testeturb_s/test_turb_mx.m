R_cm = [-2.1; 0; 0];
alt = 1000.;
mach = 0.735;
manete = 0.735;
alija_boost_on = 1;
turb_on = 1;

[thurst, rpm, m_dot, Mom, H] = ...
    turb_mx(R_cm, alt, mach, manete, alija_boost_on, turb_on);