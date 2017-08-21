// This program generates Li9/He8 events.
// Sep. 09,2009  qinghe@princeton.edu

#include "Li9He8Decay.hh"

#include "Randomize.hh"
#include <CLHEP/Random/RandBreitWigner.h>


Li9He8Decay::Li9He8Decay()
{
}

void Li9He8Decay::RandomVector(G4ThreeVector& aVec)
{
  double theta, phi;
  //double rn1 = G4UniformRand();
  double rn1 = G4UniformRand();
  double rn2 = G4UniformRand();
  
  theta = acos(1-2*rn1);
  phi = 2*pi*rn2;
  
  //aVec.SetMagThetaPhi(1.,theta,phi);
  aVec.setRThetaPhi(1.,theta,phi);
}

//Generate Li9 alpha sepectrum according data 
//Nuclear Physics A450(1990) 189-208  fig.4
double Li9He8Decay::GetLi9AlphaEnergy(int whichcase)
{
  //alpha sectra 
  double x[181],y[181];
x[0]=0.0256274;y[0]=1831.06;
x[1]=0.0633363;y[1]=2024.86;x[2]=0.101034;y[2]=2211.13;x[3]=0.119957;y[3]=2507.88;
x[4]=0.13888;y[4]=2844.46;x[5]=0.170319;y[5]=3145.64;x[6]=0.214286;y[6]=3434.87;
x[7]=0.25815;y[7]=3348.43;x[8]=0.295687;y[8]=3064.9;x[9]=0.326944;y[9]=2770.36;
x[10]=0.345638;y[10]=2441.97;x[11]=0.364344;y[11]=2179.81;x[12]=0.383038;y[12]=1921.42;
x[13]=0.407922;y[13]=1550.56;x[14]=0.432897;y[14]=1384.05;x[15]=0.457838;y[15]=1189.57;
x[16]=0.464199;y[16]=1315.73;x[17]=0.476544;y[17]=1061.86;x[18]=0.488968;y[18]=936.029;
x[19]=0.513955;y[19]=846.107;x[20]=0.538884;y[20]=718.107;x[21]=0.551309;y[21]=633.01;
x[22]=0.557487;y[22]=572.266;x[23]=0.563642;y[23]=504.472;x[24]=0.576067;y[24]=444.691;
x[25]=0.607312;y[25]=396.92;x[26]=0.6258;y[26]=278.848;x[27]=0.626018;y[27]=354.308;
x[28]=0.632001;y[28]=258.526;x[29]=0.656862;y[29]=203.433;x[30]=0.675785;y[30]=230.735;
x[31]=0.68186;y[31]=186.222;x[32]=0.694296;y[32]=166.237;x[33]=0.706675;y[33]=139.332;
x[34]=0.725415;y[34]=129.167;x[35]=0.75039;y[35]=115.296;x[36]=0.888229;y[36]=104.146;
x[37]=0.93842;y[37]=108.125;x[38]=0.982421;y[38]=122.617;x[39]=1.0074;y[39]=109.449;
x[40]=1.03881;y[40]=118.025;x[41]=1.17665;y[41]=106.611;x[42]=1.19554;y[42]=116.432;
x[43]=1.37112;y[43]=120.785;x[44]=1.40866;y[44]=110.558;x[45]=1.43994;y[45]=102.484;
x[46]=1.54651;y[46]=101.133;x[47]=1.56535;y[47]=105.018;x[48]=1.59041;y[48]=102.387;
x[49]=1.59656;y[49]=90.2576;x[50]=1.61546;y[50]=99.8223;x[51]=1.63421;y[51]=93.7139;
x[52]=1.65298;y[52]=89.0953;x[53]=1.69686;y[53]=89.0707;x[54]=1.71557;y[54]=79.5085;
x[55]=1.74074;y[55]=87.9307;x[56]=1.75318;y[56]=78.494;x[57]=1.88492;y[57]=85.6637;
x[58]=1.89738;y[58]=78.4226;x[59]=1.91607;y[59]=69.1267;x[60]=1.94116;y[60]=69.9925;
x[61]=1.96634;y[61]=78.3886;x[62]=1.99144;y[62]=80.3772;x[63]=2.00387;y[63]=70.8524;
x[64]=2.01002;y[64]=62.4587;x[65]=2.02249;y[65]=57.9045;x[66]=2.03513;y[66]=64.8556;
x[67]=2.14164;y[67]=59.3383;x[68]=2.15406;y[68]=52.3066;x[69]=2.18549;y[69]=57.1204;
x[70]=2.21056;y[70]=56.396;x[71]=2.22305;y[71]=53.6187;x[72]=2.29195;y[72]=49.6914;
x[73]=2.31701;y[73]=49.0612;x[74]=2.31701;y[74]=49.0612;x[75]=2.3609;y[75]=49.0476;
x[76]=2.49263;y[76]=52.8572;x[77]=2.50507;y[77]=47.1846;x[78]=2.50507;y[78]=47.1846;
x[79]=2.52389;y[79]=47.7774;x[80]=2.54265;y[80]=45.4228;x[81]=2.54265;y[81]=45.4228;
x[82]=2.56134;y[82]=40.0385;x[83]=2.58019;y[83]=41.5767;x[84]=2.58019;y[84]=41.5767;
x[85]=2.68073;y[85]=53.4643;x[86]=2.69943;y[86]=47.7246;x[87]=2.70559;y[87]=42.0708;
x[88]=2.71174;y[88]=37.0868;x[89]=2.73056;y[89]=37.5528;x[90]=2.74322;y[90]=42.5944;
x[91]=2.77454;y[91]=41.5258;x[92]=2.78698;y[92]=37.0692;x[93]=2.7994;y[93]=32.6765;
x[94]=2.82444;y[94]=31.0648;x[95]=2.83082;y[95]=35.2368;x[96]=2.8372;y[96]=39.969;
x[97]=2.87471;y[97]=35.227;x[98]=2.89977;y[98]=34.7803;x[99]=2.93111;y[99]=34.3378;
x[100]=2.9874;y[100]=29.507;x[101]=3.00005;y[101]=33.4684;x[102]=3.01259;y[102]=33.4658;
x[103]=3.03149;y[103]=37.0122;x[104]=3.05658;y[104]=37.4757;x[105]=3.07529;y[105]=33.4525;
x[106]=3.10033;y[106]=32.206;x[107]=3.13794;y[107]=31.7951;x[108]=3.15658;y[108]=26.6481;
x[109]=3.16297;y[109]=30.2269;x[110]=3.18181;y[110]=31.3881;x[111]=3.18797;y[111]=27.6697;
x[112]=3.19412;y[112]=24.3917;x[113]=3.21287;y[113]=22.8991;x[114]=3.22552;y[114]=25.648;
x[115]=3.2319;y[115]=29.0925;x[116]=3.25687;y[116]=25.9683;x[117]=3.34442;y[117]=20.1704;
x[118]=3.36333;y[118]=22.5908;x[119]=3.38219;y[119]=23.7563;x[120]=3.41357;y[120]=24.667;
x[121]=3.45105;y[121]=21.1992;x[122]=3.46347;y[122]=18.6871;x[123]=3.47599;y[123]=18.2204;
x[124]=3.495;y[124]=22.8584;x[125]=3.52628;y[125]=21.1892;x[126]=3.55766;y[126]=22.0015;
x[127]=3.58894;y[127]=20.3948;x[128]=3.60778;y[128]=20.913;x[129]=3.63899;y[129]=17.9737;
x[130]=3.69545;y[130]=18.6598;x[131]=3.73912;y[131]=14.6816;x[132]=3.75157;y[132]=13.4406;
x[133]=3.75796;y[133]=15.2456;x[134]=3.88329;y[134]=14.3031;x[135]=3.93996;y[135]=18.6311;
x[136]=3.99617;y[136]=14.6578;x[137]=4.0086;y[137]=13.0847;x[138]=4.01502;y[138]=15.414;
x[139]=4.03378;y[139]=14.6543;x[140]=4.04623;y[140]=13.2476;x[141]=4.14013;y[141]=11.2386;
x[142]=4.15255;y[142]=9.90679;x[143]=4.17144;y[143]=10.8194;x[144]=4.17782;y[144]=12.2724;
x[145]=4.22172;y[145]=12.4246;x[146]=4.25924;y[146]=11.0895;x[147]=4.28449;y[147]=13.3955;
x[148]=4.34105;y[148]=15.5775;x[149]=4.37201;y[149]=10.1457;x[150]=4.46601;y[150]=9.64108;
x[151]=4.5099;y[151]=9.76068;x[152]=4.51629;y[152]=11.0715;x[153]=4.55383;y[153]=10.1341;
x[154]=4.61626;y[154]=7.58054;x[155]=4.61642;y[155]=6.04361;x[156]=4.70998;y[156]=5.32303;
x[157]=4.77286;y[157]=6.50995;x[158]=4.80433;y[158]=7.47671;x[159]=4.82321;y[159]=8.06317;
x[160]=4.8796;y[160]=7.76119;x[161]=4.96742;y[161]=8.15803;x[162]=5.09882;y[162]=6.09977;
x[163]=5.13653;y[163]=6.74537;x[164]=5.19263;y[164]=4.7377;x[165]=5.25514;y[165]=3.82235;
x[166]=5.33026;y[166]=3.36807;x[167]=5.3363;y[167]=2.61743;x[168]=5.3675;y[168]=2.22137;
x[169]=5.43639;y[169]=2.05867;x[170]=5.58667;y[170]=1.66001;x[171]=5.66189;y[171]=1.63843;
x[172]=5.71198;y[172]=1.51861;x[173]=5.84989;y[173]=1.47951;x[174]=5.9878;y[174]=1.45971;
x[175]=6.11946;y[175]=1.4585;x[176]=6.18844;y[176]=1.47636;x[177]=6.2511;y[177]=1.42101;
x[178]=6.45168;y[178]=1.34943;x[179]=6.65234;y[179]=1.39967;x[180]=6.92197;y[180]=1.45114;
 
  bool accept = 0;
  double alphaenergy = -1;
  if( whichcase == 1 ){//case 1, from x[0] to x[44]
    while(!accept){
      double sampling = G4UniformRand()*x[44];
      //find y value of the sampling point 
      double yvalue = 0;
      for(int i=0;i<43;i++){
	if(sampling > x[i] && sampling < x[i+1]){
	  yvalue = (y[i]+y[i+1])/2.;
	  break;
	}
      }

      double max = 3500.0; //maximum of case 1
      if( yvalue > G4UniformRand()*max ){
	alphaenergy = sampling;
	accept = 1;
      }
    }
  }
  if( whichcase == 2 ){//case 2, from x[44] to x[180]
    while(!accept){
      double sampling = G4UniformRand()*(7.0-x[44])+x[44];
      //find y value of the sampling point 
      double yvalue = 0;
      for(int i=44;i<180;i++){
	if(sampling > x[i] && sampling < x[i+1]){
	  yvalue = (y[i]+y[i+1])/2.;
	  break;
	}
      }

      double max = 111.0; //maximum of case 2
      if( yvalue > G4UniformRand()*max ){
	alphaenergy = sampling;
	accept = 1;
      }
    }
  }

  return alphaenergy;
}

//Generate He8 neutron sepectrum according data 
//Nuclear Physics A366(1981) 461-468  fig.4
double Li9He8Decay::GetHe8NeutronEnergy()
{
  double x[2000];
  double y[2000];
x[0]=0.153478;y[0]=1.6369;
x[1]=0.219561;y[1]=1.9881;x[2]=0.297456;y[2]=2.35119;x[3]=0.367927;y[3]=2.32143;
x[4]=0.442927;y[4]=1.94643;x[5]=0.531232;y[5]=1.96429;x[6]=0.60873;y[6]=2.22619;
x[7]=0.684524;y[7]=2.05357;x[8]=0.778758;y[8]=2.08333;x[9]=0.855089;y[9]=2.04762;
x[10]=0.92458;y[10]=1.76786;x[11]=1.00093;y[11]=1.7381;x[12]=1.08301;y[12]=1.66667;
x[13]=1.17085;y[13]=1.56548;x[14]=1.22908;y[14]=1.41667;x[15]=1.31653;y[15]=1.21429;
x[16]=1.38128;y[16]=1.22619;x[17]=1.48088;y[17]=1.125;x[18]=1.55124;y[18]=1.06548;
x[19]=1.63894;y[19]=0.928571;x[20]=1.7152;y[20]=0.875;x[21]=1.79743;y[21]=0.845238;
x[22]=1.87967;y[22]=0.815476;x[23]=1.9497;y[23]=0.672619;x[24]=2.02633;y[24]=0.714286;
x[25]=2.10212;y[25]=0.541667;x[26]=2.17264;y[26]=0.52381;x[27]=2.2489;y[27]=0.470238;
x[28]=2.33665;y[28]=0.345238;x[29]=2.41349;y[29]=0.440476;x[30]=2.49542;y[30]=0.333333;
x[31]=2.57782;y[31]=0.345238;x[32]=2.65437;y[32]=0.363095;x[33]=2.73049;y[33]=0.27381;
x[34]=2.80717;y[34]=0.327381;x[35]=2.88336;y[35]=0.255952;x[36]=2.96555;y[36]=0.214286;
x[37]=3.04797;y[37]=0.232143;x[38]=3.11811;y[38]=0.119048;x[39]=3.19484;y[39]=0.184524;
x[40]=3.27659;y[40]=0.0297619;x[41]=3.34753;y[41]=0.119048;x[42]=3.43574;y[42]=0.113095;

  bool accept = 0;
  double nenergy = 0;
  while(!accept){
    double sampling = G4UniformRand()*4;
    //find y value of the sampling point 
    double yvalue = 0;
    for(int i=0;i<42;i++){
      if(sampling > x[i] && sampling < x[i+1]){
	yvalue = (y[i]+y[i+1])/2.;
	break;
      }
    }
    double max = 2.5; //maximum 
    if( yvalue > G4UniformRand()*max ){
      nenergy = sampling;
      accept = 1;
    }
  }
  return nenergy;
}  

// Chooses an intermediate energy for decays with broad levels
// by thowing according to a Breit-Wigner form.  It is constrained,
// however, to be >0 and less than the maximum available energy
double Li9He8Decay::GetIntermediateEnergy(double peak, double width, double max)
{
  if (width==0) return peak;

  double energy= -1;
  do {
        energy = RandBreitWigner::shoot(peak,width);
    //energy = m_breitwigner()*width+peak;
  } while (energy < 0 || energy > max);
  
  return energy;
}

//This Fermi function is copyed from Geant4
double Li9He8Decay::FermiFunc(double T, double Z) {
  double A1, A2;
  double P, U, S, Y;
  double F2;
  double E = T+1.;  
  P=std::sqrt(E*E-1.0) ;
  U=Z/137.0;
  S=std::sqrt(1.0-U*U) - 1.;
  Y = 2*pi*U*E/P;
  A1 = U*U*E*E + P*P/4.;
  A2 = std::fabs(Y/(1-std::exp(-Y)));
  F2 = std::pow(A1,S) * A2; 
  return F2;
}
// Unnormalized beta spectrum (allowed approximation, including fermi factor)
// Z is for daughter nucleus, i.e. 3 for He-8, 4 for Li-9
double Li9He8Decay::BetaSpectrum(double E, double QOfDecay, double Z)
{
  if(E>QOfDecay) return 0;
  else{
    return FermiFunc(E/electron_mass_c2, Z)*sqrt(E*E+2*electron_mass_c2*E)*(QOfDecay-E)*(QOfDecay-E)*(E+electron_mass_c2);
  }
}

//Get the spectrum max by sampling 100 events
double Li9He8Decay::GetSpectrumMax(double QOfDecay, int Z)
{
  double max = 0;
  int nbins = 100;
  double de = QOfDecay/nbins;
  for(int i=0; i<100; i++){
    double E = de*(i+1);
    double betaE = FermiFunc(E/electron_mass_c2, Z)*sqrt(E*E+2*electron_mass_c2*E)*(QOfDecay-E)*(QOfDecay-E)*(E+electron_mass_c2);
    if(betaE > max) max = betaE;
  }

  return max*1.2; //enlarge a little bit to assure it is larger than max
}
// Uses accept/reject method to generate electron energy according to beta spectrum
// the Z is for the daughter nucleus
double Li9He8Decay::GetElectronEnergy(double QOfDecay, int Z, double max)
{
  double trialE, rn_y;
  do {
    trialE = QOfDecay*G4UniformRand();
    rn_y = max*G4UniformRand();
  } while ( rn_y > BetaSpectrum(trialE,QOfDecay,Z) );
  
  return trialE;
}

//This is the neutron spectrum line shape for Li9 2.43MeV state 
//ref. Nuclear Physics A450(1990) 189-208 
double Li9He8Decay::Li9NeutronLineShape1(double x)
{
  double mean  = 0.2279;
  double width = 0.3266;
  double norm  = 674.1;
  double mean2 = 0.6661;
  double width2= 0.05699;
  double norm2 = 24.78;

  double sum = norm*width/((x-mean)*(x-mean)+width*width/4.);
  sum += norm2*width2/((x-mean2)*(x-mean2)+width2*width2/4.);  
  return sum;
}

//This is the neutron spectrum line shape for Li9 2.43MeV state 
//ref. Nuclear Physics A450(1990) 189-208 
double Li9He8Decay::Li9NeutronLineShape2(double x)
{
  double mean  = 1.253;
  double width = 0.8205;
  double norm  = 219;

  return norm*width/((x-mean)*(x-mean)+width*width/4.);
}
//This is the neutron spectrum line shape for Li9 2.78MeV state 
//ref. Nuclear Physics A450(1990) 189-208 
double Li9He8Decay::Li9NeutronLineShape3(double x)
{
  double mean  = 0.8;
  double width = 1.5;
  double norm  = 100;

  return norm*width/((x-mean)*(x-mean)+width*width/4.);
}

//Get Li9 neutron spectrum from the above line shapes 
double Li9He8Decay::GetLi9NeutronEnergy(int whichshape, double max)
{
  bool accept = 0;
  double trial_E = 0;
  double shapeV;
  while(!accept){
    double rand1 = G4UniformRand()*3.;//random energy
    double rand2 = G4UniformRand()*max;
    if(whichshape == 1) {
      shapeV = Li9NeutronLineShape1(rand1);
    }
    else if(whichshape == 2) {
      shapeV = Li9NeutronLineShape2(rand1);
    }
    else if(whichshape == 3) {
      rand1 = G4UniformRand()*10.;
      shapeV = Li9NeutronLineShape3(rand1);
    }
    else {
      cout << "Error! The first parameter must be 1, 2 or 3." << endl; 
      break;
    }
    if(rand2 < shapeV) {//accept
      trial_E = rand1;
      accept=1;
    }
  }    

  return trial_E;
}

// For broad states, the final energy of the daughter nucleus is thrown according 
// to a Breit-Wigner form
//by default, only decays with neutrons are considered.
//for complete decay, use the -complete_decay option
void Li9He8Decay::Li9Decay(G4ThreeVector &pElectron,G4ThreeVector &pNeutron, G4ThreeVector &pAlpha1,
		      G4ThreeVector &pAlpha2,double alpha_mass,bool complete_decay)
{
  double rn;
  //default is to skip the decay without neutron
  if(complete_decay) rn= G4UniformRand();
  else rn = G4UniformRand()*(1.-0.492)+0.492;//start from 0.492
  double intermediateEnergy = 0;
  double betaenergy = 0;
  double nenergy = 0;
  double aenergy1 = 0;
  double aenergy2 = 0;

  double max = 0;
  if (rn<0.492){
    max = GetSpectrumMax(13.6067,4);
    betaenergy = GetElectronEnergy(13.6067,4,max);
  }
  else if (rn<0.789) {//case 1 for alpha spectra
    intermediateEnergy = GetIntermediateEnergy(2.429,0.00077,13.6067);
    max = GetSpectrumMax(13.6067-intermediateEnergy,4);
    betaenergy = GetElectronEnergy(13.6067-intermediateEnergy,4,max);
    nenergy = GetLi9NeutronEnergy(1,8264);
    aenergy1 = GetLi9AlphaEnergy(1);
    aenergy2 = GetLi9AlphaEnergy(1);
  }
  else if (rn < 0.947) {//case 1 for alpha spectra
    intermediateEnergy = GetIntermediateEnergy(2.78,1.08,13.6067);
    max = GetSpectrumMax(13.6067-intermediateEnergy,4);
    betaenergy = GetElectronEnergy(13.6067-intermediateEnergy,4,max);
    nenergy = GetLi9NeutronEnergy(2,1068);
    aenergy1 = GetLi9AlphaEnergy(1);
    aenergy2 = GetLi9AlphaEnergy(1);
  }
  else if (rn < 0.962) {//case 2 for alpha spectra
    intermediateEnergy = GetIntermediateEnergy(7.94,1.0,13.6067);
    max = GetSpectrumMax(13.6067-intermediateEnergy,4);
    betaenergy = GetElectronEnergy(13.6067-intermediateEnergy,4,max);
    nenergy = GetLi9NeutronEnergy(3,300);
    aenergy1 = GetLi9AlphaEnergy(2);
    aenergy2 = GetLi9AlphaEnergy(2);
  }
  else if (rn < 0.973) {//case 2 for alpha spectra
    intermediateEnergy = GetIntermediateEnergy(11.283,0.575,13.6067);
    max = GetSpectrumMax(13.6067-intermediateEnergy,4);
    betaenergy = GetElectronEnergy(13.6067-intermediateEnergy,4,max);
    nenergy = GetLi9NeutronEnergy(3,300);
    aenergy1 = GetLi9AlphaEnergy(2);
    aenergy2 = GetLi9AlphaEnergy(2);
  }
  else {//case 2 for alpha spectra
    intermediateEnergy = GetIntermediateEnergy(11.81,0.400,13.6067);
    max = GetSpectrumMax(13.6067-intermediateEnergy,4);
    betaenergy = GetElectronEnergy(13.6067-intermediateEnergy,4,max);
    nenergy = GetLi9NeutronEnergy(3,300);
    aenergy1 = GetLi9AlphaEnergy(2);
    aenergy2 = GetLi9AlphaEnergy(2);
  }

  // Electron momentum vector is isotropic
  double eMom = sqrt(2*betaenergy*electron_mass_c2+betaenergy*betaenergy);
  eMom *= MeV;
  RandomVector(pElectron);
  pElectron *= eMom;

  // Neutron momentum vector is isotropic
  if(nenergy>0){//there is neutron come out
    double nMom = sqrt(2*nenergy*neutron_mass_c2+nenergy*nenergy);
    nMom *= MeV;
    RandomVector(pNeutron);
    pNeutron *= nMom;

    //alpha momentum setup isotropically
    double aMom1 = sqrt(2*aenergy1*alpha_mass+aenergy1*aenergy1);
    aMom1 *= MeV;
    RandomVector(pAlpha1);
    pAlpha1 *= aMom1;

    //alpha2
    double aMom2 = sqrt(2*aenergy2*alpha_mass+aenergy2*aenergy2);
    aMom2 *= MeV;
    RandomVector(pAlpha2);
    pAlpha2 *= aMom2;
  }  
}

//He8 decay
//by default, only decays with neutrons are considered.
//for complete decay, use the -complete_decay option
//ref. Nucler Physics A366 (1981) 461-468, Nuclear Physics A487 (1988) 269-278 
void Li9He8Decay::He8Decay(G4ThreeVector &pElectron, G4ThreeVector &pNeutron, G4ThreeVector &pGamma,
	      bool complete_decay)
{
  double rn;
  //degault is to skip the decay without neutron
  if(complete_decay) rn= G4UniformRand();
  else rn = G4UniformRand()*(1-0.84)+0.84; //start from 0.84
  double intermediateEnergy = 0;
  double betaenergy = 0;
  double nenergy = 0;
  double gammaenergy = 0;

  double max = 0;
  if (rn<0.84){//84% to the 0.9808MeV state, no neutron
    max = GetSpectrumMax(10.649-0.9808,3);//(Q,Z)
    betaenergy = GetElectronEnergy(10.649-0.9808,3,max);
    gammaenergy = 0.9808;
  }
  else {//16% neutron
    nenergy = GetHe8NeutronEnergy();
    if( G4UniformRand()<0.32 ){//32% gamma 
      gammaenergy = 0.478;
    }
    double He8Br = G4UniformRand();
    if( He8Br<7.8/(7.8+2.6) ){//3.21 MeV state
      intermediateEnergy = GetIntermediateEnergy(3.21,1.0,10.649);
      max = GetSpectrumMax(10.649-intermediateEnergy,3);
      betaenergy = GetElectronEnergy(10.649-intermediateEnergy,3,max);
    }
    else {//5.4 MeV state
      intermediateEnergy = GetIntermediateEnergy(5.4,0.65,10.649);
      max = GetSpectrumMax(10.649-intermediateEnergy,3);
      betaenergy = GetElectronEnergy(10.649-intermediateEnergy,3,max);
    }
  }

  // Electron momentum vector is isotropic
  double eMom = sqrt(2*betaenergy*electron_mass_c2+betaenergy*betaenergy);
  eMom *= MeV;
  RandomVector(pElectron);
  pElectron *= eMom;

  // Neutron momentum vector is isotropic
  if(nenergy>0){//there is neutron come out
    //neutron momentum setup isotropically
    double nMom = sqrt(2*nenergy*neutron_mass_c2+nenergy*nenergy);
    nMom *= MeV;
    RandomVector(pNeutron);
    pNeutron *= nMom;
  }

  //gamma momentum setup isotropically
  if(gammaenergy>0){
    RandomVector(pGamma);
    pGamma *= gammaenergy*MeV;
  }
}


