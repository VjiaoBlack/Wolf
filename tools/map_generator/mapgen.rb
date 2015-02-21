#!/usr/bin/env ruby

module MapGen
  class Map
    # Generates a new map with the given options and an optional constructor.
    def initialize(options={}, &constructor)
      options     = { name:        'untitled.map',
                      destination: Dir.pwd,
                      overwrite:   false,
                      dimensions:  { width: 0, height: 0 }
                    }.merge options
      @name       = options[:name]
      @lines      = []
      @bounding_box = [options[:dimensions][:width],  # memoized smallest x
                       options[:dimensions][:height], # memoized smallest y
                       options[:dimensions][:width],  # memoized greatest x
                       options[:dimensions][:height]] # memoized greatest y
      if block_given?
        construct &constructor
        write_to  options[:destination], overwrite=options[:overwrite]
       end
    end

    # A wrapper to instance_eval.
    def construct(&constructor)
      instance_eval &constructor
    end 

    # Writes the map out to a destination. If overwrite is false, this will NOT overwrite
    # the file if it already exists.
    def write_to(destination, overwrite=false)
      destination = File.join(destination, "#{@name}") unless File.file?  destination
      if !overwrite && File.exists?(destination)
        raise "File '#{destination}' already exists!"
      end

      # Translate the map so that every point is positive.
      translate(-@bounding_box[0], -@bounding_box[1])
      
      File.open(destination, "w") do |file|
        file.puts "#{@lines.size} #{@bounding_box[2]} #{@bounding_box[3]}"
        @lines.each { |line| file.puts line.join(' ') }
      end
    end
    
    ###################################
    # The Geometric Drawing Functions #
    ###################################


    def translate(dx, dy)
      @bounding_box[0] += dx
      @bounding_box[1] += dy
      @bounding_box[2] += dx
      @bounding_box[3] += dy

      @lines.map! do |line|
        [line[0] + dx, line[1] + dy, line[2] + dx, line[3] + dy]
      end
    end

    # Adds a line to the map and updates the dimensions of the map to encompass it.
    def directed_line(x0, y0, x1, y1)
      @lines <<= [x0, y0, x1, y1]
      @bounding_box[0] = [@bounding_box[0], x0].min
      @bounding_box[1] = [@bounding_box[1], y0].min
      @bounding_box[2] = [@bounding_box[2], x1].max
      @bounding_box[3] = [@bounding_box[3], y1].max
    end

    # Draws a strip of lines to the map.
    def line_strip(*points)
      shifted_points = Array.new(points)
      shifted_points.shift
      shifted_points.zip(points).each do |line|
        directed_line line[1][0], line[1][1], line[0][0], line[0][1]
      end
    end
    
    # Wraps to a call of `line_strip`. It adds a line from the last point to the first.
    # ensuring that the structure is closed.
    def polygon(*points)
      points <<= points[0]
      line_strip(*points)
    end

    # draws a rectangle with the given options:
    #   position
    #     centered: the center point of the sphere is here
    #     top_left: specify the top left corner of the box
    #   dimensions - the dimensions of the rectangle. If a single number is given, it is turned into an array
    def rectangle(options)
      options = { position: [:centered, 0, 0], dimensions: [0, 0] }.merge options
      x0, y0, x1, y1 = 0, 0, 0, 0

      options[:dimensions] = Array.new(2, options[:dimensions]) unless options[:dimensions].kind_of? Array
      
      case options[:position][0]
      when :centered
        x0 = options[:position][1] - options[:dimensions][0] / 2
        y0 = options[:position][2] - options[:dimensions][1] / 2
        x1 = options[:position][1] + options[:dimensions][0] / 2
        y1 = options[:position][2] + options[:dimensions][1] / 2
      when :top_left
        x0 = options[:position][1]
        y0 = options[:position][2]
        x1 = options[:position][1] + options[:dimensions][0]
        y1 = options[:position][2] + options[:dimensions][1]
      end

      polygon([x0, y0], [x1, y0], [x1, y1], [x0, y1])
    end
  end
end
