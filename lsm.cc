#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <random>

#define NEURON 1776

std::random_device qdev ;
std::uniform_real_distribution < long double > rweight ( 0.0, 1.0 ) ; //connection strength
std::uniform_real_distribution < long double > rscan ( -1.0, 1.0 ) ; //input

int main ( )
{
	//int a = true ? 69 : 4;
	long double * neuron = new long double [ NEURON ] ;
	long double * buf = new long double [ NEURON ] ;
	long double * weight = new long double [ NEURON * NEURON ] ; //[x][y] = [x*NEURON+y]
	for ( int i = 0 ; i < NEURON ; i++ )
	{
		neuron [ i ] = 0.0 ;
		buf [ i ] = 0.0 ;
		//random weights (liquid state machine)
		for ( int j = 0 ; j < NEURON ; j++ )
		{
			weight [ i * NEURON + j ] = rweight ( qdev ) ;
		}
	}
	while ( 1 )
	{
		//Inputs here???
		for ( int k = 0 ; k < 1 ; k++ )
		{
			neuron [ k ] = rscan ( qdev ) ;
		}
		//Process (RT w/ BUF)
		for ( int k = 0 ; k < NEURON ; k++ )
		{
			buf [ k ] = 0.0 ;
			//Sum Inputs, y.k = sum(weight.k.i*neuron.i)
			for ( int i = 0 ; i < NEURON ; i++ )
			{
				buf [ k ] = buf [ k ] + ( neuron [ i ] * weight [ k * NEURON + i ] ) ;
			}
			buf [ k ] = sinl ( buf [ k ] ) ; //activation function SIN(X)
		}
		//Copy buf to neuron and print brain
		//usleep ( 55555 ) ; //1/60 == 60fps == 16667
		printf ( "\x1b[40m\x1b[2J\x1b[3J\x1b[1;1H" ) ;
		for ( int k = 0 ; k < NEURON ; k++ )
		{
			if ( buf [ k ] >= 0.5 )
			{
				printf("\x1b[47m ");
			}
			else
			{
				printf("\x1b[40m ");
			}
			neuron [ k ] = buf [ k ] ;
		}
		fflush ( stdout ) ;
	}
}
