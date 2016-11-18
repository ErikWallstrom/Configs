number = rand(100)
print "Guess a number betweeen 1 and 100: "

guesses = 0
while true do
	guess = gets.chomp.to_i
	guesses += 1

	if guess < 1 || guess > 100 then
		puts "That's not a number between 1 and 100, u dumbass"
		print "Guess again: "
		guesses -= 1
	elsif guess < number then
		print "Higher: "
	elsif guess > number then
		print "Lower: "
	else
		break
	end
end

print "Congratulations! You needed #{guesses} guess(es). "
if guesses == 1 then
	puts "You lucker"
elsif guesses < 7 then
	puts "Well done"
else
	puts "Are you retarded?"
end
