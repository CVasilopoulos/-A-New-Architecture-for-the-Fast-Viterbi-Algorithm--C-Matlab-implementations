 
% Encoder: [1 + D + 0 * D^2]
% Channel: AWGN, Modulation: BPSK


clc; clear all; close all;

SNR=10.^(12 /10);  % SNR in Linear Scale
seed = 100; % seed to initialize the random number generator to a default state
rng(seed);
block_length = 25;   % length of sequence
info_bits = floor(2 * rand(1, block_length));      %Information bits (0 or 1) of length block_length
        
% Assigning last and second last bit of each block of length block_length as 0
   info_bits(block_length)=0;
   info_bits(block_length - 1)=0; 


% Encoder 
code = conv([1 1 0] , info_bits);    
code(code == 2)=0;
code(code == 3)=1;

% BPSK Modulation
code= 2 * code(1:block_length)-1;   

% Decoder

% Received codebits

   input_sequence = (sqrt(SNR)*code) + randn(1, block_length);   


    % Decoding is done individually for each block of length block_length
    dist = zeros(4,block_length+1);   	%For storing minimum dist for reaching each of the 4 states
    branch_metric= zeros(8,block_length);         	%For storing Metric corresponding to each of the 8 transitions
    dist(1,1)=0;dist(2,1)=Inf;dist(3,1)=Inf;dist(4,1)=Inf; %Initialization of distances

    for i = 1 : block_length

        metric(1,i)=norm([-1]-[input_sequence(i)]);    % Metric for transition from state 00 to 00
        metric(2,i)=norm([+1]-[input_sequence(i)]);    % Metric for transition from state 00 to 01
        metric(3,i)=norm([-1]-[input_sequence(i)]);    % Metric for transition from state 10 to 00    
        metric(4,i)=norm([+1]-[input_sequence(i)]);    % Metric for transition from state 10 to 01
        metric(5,i)=norm([-1]-[input_sequence(i)]);    % Metric for transition from state 01 to 11
        metric(6,i)=norm([+1]-[input_sequence(i)]);    % Metric for transition from state 01 to 10
        metric(7,i)=norm([-1]-[input_sequence(i)]);    % Metric for transition from state 11 to 11
        metric(8,i)=norm([+1]-[input_sequence(i)]);    % Metric for transition from state 11 to 10



        temp1 = min(dist(1,i), dist(3,i));
        temp2 = min(dist(4,i), dist(2,i));
        dist(1,i+1)= temp1 + metric(1,i);    %  Minimum dist to reach state 00 at time i
        dist(2,i+1)= temp1 + metric(2,i);    %  Minimum dist to reach state 01 at time i
        dist(3,i+1)=temp2 + metric(6,i);     %   Minimum dist to reach state 10 at time i                                 
        dist(4,i+1)=temp2 + metric(7,i);     %   Minimum dist to reach state 11 at time i  

    end

% the final state has the minimum state metric
[~, state] = min(dist(:, block_length+1)); 

% Using the final state, state metrics of previous stage and branch_metrics,
% decoding recursively the previous states and bits

for ii = block_length : -1 : 1

    [state,decoded_bit] = FindPreviousStates(state,dist(:,ii));
    decoded_sequence(ii) = decoded_bit; 
    
end

if (info_bits == decoded_sequence)
    
    fprintf('Message decoded successfully! \n');
else
    
    fprintf('Message was not decoded successfully! \n');
    
end


%  info_bits = info_bits';
% decoded_sequence = decoded_sequence';
ty = info_bits - decoded_sequence;
tr = find(ty);
     

save 'Viterbi_results.mat';
