function [ xy ] = fKine( theta )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
e=5;
d=200;

xy(2,:)=d*tan(2*theta(2,:));
xy(1,:)=(e+sqrt(d^2+xy(2,:).^2)).*tan(2*theta(1,:)); 
end

