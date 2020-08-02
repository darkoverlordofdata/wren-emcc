import "lib/io/path" for Path
import "lib/io/stream" for Stream

class Main {
    construct new() {
	    System.print("Hello world")
        System.print("======================================\n")

    }
    main() { 

	    System.print("Hello world")
        System.print("-------------------------------------\n")
        System.print(Path.Cwd)
        System.print("-------------------------------------\n")

        var x = Path.new("~/GitHub/opengl-wren")
        x.Join("readme.md")
        System.print(x.ToString())
        var y = x.DirName()
        System.print(y.ToString())


        var s = Stream.new("./readme.md")
        var data = s.Read()
        System.print(data)
    }

}

// nontest
var Foo = "from foo"
System.print("ran foo module")
var z = Main.new()
z.main()
