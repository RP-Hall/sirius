function theta_send = angle_conversion_odd(theta_in)
theta_out = zeros(1,3);
theta_out(2) = theta_in(2)+90;
theta_out(3) = theta_in(3)+90;
theta_out(1) = theta_in(1);
theta_send = [-1,theta_out(2),theta_out(3),theta_out(1)];
end