def minsta_talet
    puts "Please write three numbers, separated by pressing enter: "

    tal_1 = gets.chomp.to_i
    tal_2 = gets.chomp.to_i
    tal_3 = gets.chomp.to_i
    
    if (tal_1 < tal_2)
        smallest_number = tal_1
    else 
        smallest_number = tal_2
    end

    if (smallest_number < tal_3)
        return smallest_number
    else   
        return tal_3
    end 
end

puts "The smallest number was: #{minsta_talet}" 
