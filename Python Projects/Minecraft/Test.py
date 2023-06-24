def solution(h, q):
    ## calculate the maximum index first
    ## if the input is too large, return a negative 1
    max_idx = 2**h - 1
    if max_idx < q:
        return -1
    
    # otherwise, carry on
    else:
        node_offset = 0
        continue_flag = True
        subtree_size = max_idx
        result = -1 # default result
        
        while continue_flag:
            if subtree_size == 0:
                continue_flag = False
                
            # right shift is equivalent to dividing by 2 and discarding the remainder.
            subtree_size = subtree_size >> 1
            
            # predict the left node
            left_node = node_offset + subtree_size
            
            # predict the right node
            right_node = left_node + subtree_size
            
            # calculate my node value
            my_node = right_node + 1
            
            # if either child is a match, return my node value
            if (left_node == q) or (right_node == q):
                result = my_node
                continue_flag = False
            
            # Make the current left child the offset if the index is greater than the left.
            # This effectively searches down the right subtree.
            if (q > left_node):
                node_offset = left_node
   
        return result




result = solution([4, 3, 10, 2, 8], 12)

print(result)