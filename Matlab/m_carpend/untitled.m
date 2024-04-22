wc_ = wc*2;
M_  = 100;
A_  = 0.1;
W2 = (s/M_ + wc)/(s + wc_*A_);
W2.u = 'u';
W2.y = 'e2';

bodemag(W2);