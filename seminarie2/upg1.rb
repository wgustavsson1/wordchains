#[a-zA-Z]+|\d+(?!\.)

# F-A

table = Hash.new
puts "table: " + table.to_s
file = File.open("football.txt").read
    file.each_line do |line|
        if not  line.include? "<" and not  line.include? "Team" and not line.include? "-------------------------------------------------------"
            re = /[a-zA-Z_]+|\d+(?!\.|\d\.)/
            md = line.scan(re)
            f =  md[5].to_i
            a = md [6].to_i
            team = md[0]
            diff = f - a
            table[diff] = team

        end
    end
puts table
table = table.sort_by { |key| key }.reverse
puts table


#Fråga 1: Aston villa har minst målskillnad -1

