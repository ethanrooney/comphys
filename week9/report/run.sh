#!/bin/bash

n=$1
l=$2
kt=$3
dx=$4
dv=$5

#		NumP	L	kt	dx	dv	time	timestep
./gas	$n		$l	$kt	$dx	$dv	10000		50			> out_N${n}_L${l}_kT${kt}_dx${dx}_dv${dv}.log
