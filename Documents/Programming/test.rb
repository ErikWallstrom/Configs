arr = [3, 323, "Hello", true, "lulz"]

arr.each do |x|
	puts x
end

puts arr 		#last value
puts arr[-1] 	#last value
puts arr.last  	#last value, duh

arr.push 3

arr.each do |x|
	puts x
end

new_arr = ["my_string", 3.141592653589]
arr += new_arr
arr.pop
arr.each do |x|
	puts x
end

