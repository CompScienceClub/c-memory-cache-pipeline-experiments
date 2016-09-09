<?php

    $size = 100000;
    $iter = 1000;

    $x = array_pad([], $size, 1.0);
    $y = array_pad([], $size, 1.0);

    $t = time() + microtime(true);
    for ($i=0;$i<$iter;$i++){
        for ($j=0;$j<$size;$j++){
            $z = $x[$j] + $y[$j];
        }
    }
    $p = sprintf("%.1f\n", 1.e-6 * $size * $iter / (time() + microtime(true) - $t));
    echo $p;
