import "io" for Path, Stream

class Main {
    construct new() { }
    main() { 

	    System.print("Hello world")

        var x = Path.new(Path.Cwd)
        x.Join("readme.md")
        System.print("-------------------------------------\n")
        System.print(Path.Cwd)
        System.print(x.ToString())
        System.print("-------------------------------------\n")

        var s = Stream.new(x.ToString())
        var data = s.Read()
        System.print(data)
    }

}

var z = Main.new()
z.main()
