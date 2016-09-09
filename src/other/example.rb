SIZE = 1000000
ITER = 100

a = Array.new(SIZE, 1.0)
b = Array.new(SIZE, 1.0)

t = Time.now
(1..ITER).each do 
    (0..SIZE-1).each do |i|
        a[i] + b[i]
    end
end
puts "%.1f" % (1.0e-6 * SIZE * ITER / (Time.now - t))

