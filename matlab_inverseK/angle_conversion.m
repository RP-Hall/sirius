function theta_out = angle_conversion(theta_in)
theta_out = zeros(1,3);
theta_out(2) = theta_in(2)+90;
theta_out(3) = theta_in(3)+90;
theta_out(1) = 180+theta_in(1);
end