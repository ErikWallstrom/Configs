def minsta_talet
	puts "Please write three numbers, separated by pressing enter: "

	tal_1 = gets.chomp.to_i
	tal_2 = gets.chomp.to_i
	tal_3 = gets.chomp.to_i

	smallest = tal_1
	if(smallest > tal_2)
		smallest = tal_2
	end
	if(smallest > tal_3)
		smallest = tal_3
	end
	return smallest
end

puts "The smallest number was: #{minsta_talet}"
