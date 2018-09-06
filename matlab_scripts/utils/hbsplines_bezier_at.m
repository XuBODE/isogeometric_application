function Pip = hbsplines_bezier_at(Pts,P,W,Id,S,C,N,params)
% check if the point lie in which cell
num_points = size(Pts,1);
p1 = params.p1;
p2 = params.p2;
for i = 1:num_points
    xi = Pts(i,1);
    eta = Pts(i,2);
    found = 0;
    for c = 1:length(N)
        if xi>=S{c}(1,1) && xi<=S{c}(1,2) && eta>=S{c}(2,1) && eta<=S{c}(2,2)
            e = c;
            found = 1;
            break;
        end
    end
    if found == 0
        error(['the sampling point is not found']);
    end

    % extract the weight and nodal coordinates
    We = zeros(length(N{e}),1);
    Pe = zeros(length(N{e}),3);
    for n = 1:length(N{e})
        for b = 1:length(W)
            if Id(b) == N{e}(n)
                We(n) = W(b);
                Pe(n,:) = P(b,:);
            end
        end
    end

    % compute the local point
    local_xi = (xi-S{e}(1,1)) / (S{e}(1,2)-S{e}(1,1));
    local_eta = (eta-S{e}(2,1)) / (S{e}(2,2)-S{e}(2,1));

    % compute the Bezier shape function at local point
    B = zeros((p1+1)*(p2+1),1);
    for k = 0:p1
        y_xi = bezier(local_xi,k,p1);
        for l = 0:p2
            y_eta  = bezier(local_eta,l,p2);
            num = k*(p2+1)+l+1;
            B(num) = y_xi * y_eta;
        end
    end

    % compute the NURBS shape function
    Ne = C{e} * B;
    Re = We .* Ne / dot(We,Ne);
    Pip(i,:) = Re' * Pe;
end
