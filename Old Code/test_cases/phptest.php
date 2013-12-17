<?php
$sum = 0;

for ($i = 2; $i < 100; $i++) {
	$total = 0;
	for ($j = 1; $j < $i; $j++) {
		if ($i%$j == 0)
		{
			$total += $j;
		}
	}
	if ($total > $i) {
		echo $i."\t".$total."\n";
	}
}

?>
