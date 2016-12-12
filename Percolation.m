clear
clf

%read data
m=csvread('percolation.csv');
pValue = m(:,1);
n = m(:,2);
n=smooth(smooth(n));

%plot p against n
subplot(2,1,1);
plot(pValue, n);
xlabel('p');
ylabel('fraction of successful grids');

%plot differential
dn= diff(n);
dn=smooth(smooth(dn));
dn = [0; dn]; %adds zero to the start to keep it same size
subplot(2,1,2);
plot(pValue, dn);
xlabel('p');
ylabel('first differential of fraction of successful grids');


%finding max gradient
[max,index] = max(dn);
%Find the value of p_c
pc = pValue(index); 