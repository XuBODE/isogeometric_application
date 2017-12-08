knots = {};
knots{1} = [ 0 0 0 1 1 1];
knots{2} = [ 0 0 1 1];
coefs = zeros(4,3,2);
coefs(:,1,1) = [ 1 0 0 1];
coefs(:,2,1) = [ 0.707107 4.32978e-17 0.707107 0.707107];
coefs(:,3,1) = [ 2.22045e-16 6.12323e-17 1 1];
coefs(:,1,2) = [ 2 0 0 1];
coefs(:,2,2) = [ 1.41421 1.41421 0 0.707107];
coefs(:,3,2) = [ 4.44089e-16 2 0 1];
nurbs = nrbmak(coefs,knots);
