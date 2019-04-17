tic
clc;
clear all;
close all;
%%Divides in section.
wA=rand(6,2);
wB=rand(2,6);
wb=rand(6,1);

s1=[25.0 24.0 20.0 15.0 10.0 8.0 6.0 4.0 2.50 2.00 1.80 1.70 1.60 1.40 1.30 1.10 1.00 0.90 0.80 0.70 0.60 0.50 0.40 0.30 0.20 0.19 0.18 0.17 0.16 0.15 0.14 0.10];
s2=[23.0 20.0 19.0 15.0 10.0 8.0 6.0 4.0 2.50 2.00 1.80 1.70 1.60 1.40 1.30 1.10 1.00 0.90 0.80 0.70 0.60 0.50 0.40 0.30 0.20 0.19 0.18 0.17 0.16 0.15 0.14 0.10];

vld=[0.75 0.75 0.75 0.75 0.75 0.75 0.75 0.75 0.9 1 1 1 0.9 0.89 0.87 0.85 0.85 0.82 .80 .80 .78 .76 .75 .75 .75 .8 .85 .85 .85 .85 .85 .85];
vrd=[0 0 0 0 0 0.5 0.5 0.7 0.8 1 1 1 0.8 0.78 0.76 .74 .71 .71 .70 .70 .68 .66 0 0 0 0 0 0 0 0 0 0];

b=1;
eta=0.01;
    for i=1:10000
    for j=1:32
    %%feed forward
        hA=s1(j)*wA(:,1)+s2(j)*wA(:,2)+b*wb;
        vA=1./(1+exp(-hA));
        hB=wB*vA;

        vl=hB(1);
        vr=hB(2);
        E1(j)=0.5*(vld(j)-vl)^2;
        E2(j)=0.5*(vrd(j)-vr)^2;

        %%back propagation
        delb1=vld(j)-vl;
        delb2=vrd(j)-vr;
        wB1new=wB(1,:)+eta*delb1.*vA';
        wB2new=wB(2,:)+eta*delb2.*vA';

        dela=vA.*(1-vA).*(wB(1,:)*delb1+wB(2,:)*delb2)';
        wA1new=wA(:,1)+eta*dela*s1(j);
        wA2new=wA(:,2)+eta*dela*s2(j);
        
        wbnew=wb+eta*dela*b;
        wA(:,1)=wA1new;
        wA(:,2)=wA2new;
        wB(1,:)=wB1new;
        wB(2,:)=wB2new;
        wb=wbnew;
    end
      E_itr1(i)=max(E1);
      E_itr2(i)=max(E2);
      if(E_itr1(i)<.000000000001&&E_itr2(i)<.000000000001)
         break;
     end
    end
    iterations=i;
    disp(iterations);
    
    figure(1)
plot(E_itr1);
hold on
plot(E_itr2);
 for j=1:32
    %%feed forward
        hA=s1(j)*wA(:,1)+s2(j)*wA(:,2)+b*wb;
        vA=1./(1+exp(-hA));
        hB=wB*vA;

        vl(j)=hB(1);
        vr(j)=hB(2);
 end


toc
 
