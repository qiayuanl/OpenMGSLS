function [ theta ] = iKine1( xy )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

d=200;

theta(1,:) = atan(xy(1,:)/d)/2;
theta(2,:) = atan(xy(2,:)/d)/2;

end

