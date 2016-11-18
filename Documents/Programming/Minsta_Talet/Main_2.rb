def minsta_talet
    puts "Please write three numbers, separated by pressing enter: "

    tal_1 = gets.chomp.to_i
    tal_2 = gets.chomp.to_i
    tal_3 = gets.chomp.to_i
    
    if(tal_1 < tal_2)
        if(tal_1 < tal_3)
            return tal_1
        else
            return tal_3
        end
    else
        if(tal_2 < tal_3)
            return tal_2
        else
            return tal_3
        end
    end
end

puts "The smallest number was: #{minsta_talet}" 
