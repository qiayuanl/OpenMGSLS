function [ theta ] = iKine0( xy )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
e=5;
d=200;

theta(2,:) = atan(xy(2,:)/d)/2;
theta(1,:) = atan(xy(1,:)./(e+sqrt(d^2+xy(2,:).^2)))./2;

end

