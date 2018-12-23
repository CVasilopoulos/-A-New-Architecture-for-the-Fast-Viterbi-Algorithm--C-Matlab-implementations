function [previous_state, decoded_bit] = FindPreviousStates(current_state,... 
                                            dist_prev)

    if(current_state == 1)
        
        if(dist_prev(1) <= dist_prev(3))
            
            previous_state = 1;
            
        else
            
            previous_state = 3;
            
        end
        
        decoded_bit = 0;
        
    end
    
    if(current_state == 2)
        if(dist_prev(1) <= dist_prev(3))
            previous_state=1;
        else
            previous_state = 3;
        end
        
        decoded_bit = 1;
        
    end
    
    if(current_state == 3)
        
        if(dist_prev(2) <= dist_prev(4))
            
            previous_state = 2;
            
        else
            
            previous_state = 4;
            
        end
        
        decoded_bit = 0;
        
    end
    
    if(current_state == 4) 
        
        if(dist_prev(2) <= dist_prev(4))
            
            previous_state = 2;
            
        else
            
            previous_state = 4;
            
        end
        
        decoded_bit = 1;
        
    end
    
end