print "Please write the text you want to translate: "
text = gets.chomp

translated_text = ""
text.each_char do |c|
	c = c.downcase
	if c.match(/\A[^aouåeiyäö]/) && c.match(/^[[:alpha:]]$/) then
		translated_text += (c + "o" + c);
	else
		translated_text += c
	end
end

puts "Translation: " + translated_text
