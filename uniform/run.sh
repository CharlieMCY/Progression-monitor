 #!/bin/bash
        for i in `seq 1 12`;
		do
            cd traces$i
			cp ../safety_mon .
			cp ../func.txt .
			./safety_mon
			cd ..
        done
        
