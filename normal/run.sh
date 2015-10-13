 #!/bin/bash
        for i in `seq 1 100`;
		do
#		    ./create
#		    mkdir traces$i
#		    mv trace*.txt traces$i
            cd traces$i
			cp ../safety_mon .
			cp ../input.txt .
			cp ../func.txt .
			./safety_mon
			cd ..
        done
        
