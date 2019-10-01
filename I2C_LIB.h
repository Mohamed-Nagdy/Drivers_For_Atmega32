#ifndef 
/*
	this header file written by Mohamed Nagdy .
	this header file is for I2C Protocol for AVR Micro Controller
	this file has the configurations of both Master and Slave If you need to use the controller as master or slave
	you can change the transmit speed by change the value of TWBR Register
	
	Created in 2-10-2019 
*/
/******************************************************************************************************************
				these functions below are common between the master and slave of i2c protocol
********************************************************************************************************************/

// ********** this function to write on the data bus the address of slave and the operation read or write *********
void i2c_write_addr_and_rw(unsigned char addrAndRW)
{
	TWDR = addrAndRW;		// set the address to the data register of the two wire
	TWCR = (1 << TWINT) | (1 << TWEN);		// set the interrupt to and the enable for two wire
	while((TWCR & (1 << TWINT)) == 0);		// wait till it finish 
}



// ******************************* this function to write a singe byte on the data line ****************************
void i2c_write_data(unsigned char addrAndRW)
{
	TWDR = addrAndRW;		// set the address to the data register of the two wire
	TWCR = (1 << TWINT) | (1 << TWEN);		// set the interrupt to and the enable for two wire
	while((TWCR & (1 << TWINT)) == 0);		// wait till it finish
}



// ****************************** this function to start the i2c protocol *******************************************
void i2c_start()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);		// set the interrupt and enable and the start flags
	while((TWCR & (1 << TWINT)) == 0);						// wait till the transfer finish
}



// ******************************* this function to stop the i2c protocol *******************************************
void i2c_stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);		// set the interrupt and enable and the stop flags
}



// ****************************** this function to read single byte from data line ***********************************
unsigned char i2c_read_data(unsigned char readStatus)
{
	if (readStatus == 0)		// if i send 0 it will send ACK after recive every byte and recive another one
	{
		TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);		// set the interrupt and enable and the ACK flags
	}
	else			// else i send any other number it will just recieve one byte
	{
		TWCR = (1 << TWEN) | (1 << TWINT);		// set the interrupt and enable flags
	}
	while((TWCR & (1 << TWINT)) == 0);			// wait till it finish
	return TWDR;								// return the byte it just recieved
}

// end of general functions



/******************************************************************************************************************
	these functions below are for initialize the slave and to listen the to the data line till the master address it
********************************************************************************************************************/


// ************************ initialize atmega 32 as a slave in i2c protocol ***************************************
void i2c_init_slave(unsigned char slaveAddress)
{
	TWCR = 0X04;										// enable the TWI module
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// init TWI module
	TWAR = slaveAddress;								// set the address of this slave as i like
}



// ****************** make the slave lestine to the channel till the master addressing it *************************
void i2c_lestin()
{
	while((TWCR & (1 << TWINT)) == 0);					// wait to be addressed
}


/******************************************************************************************************************
							this functions below if for initialize the master
********************************************************************************************************************/


// ************************ initialize atmega 32 as a master in i2c protocol ***************************************
void i2c_init_master()
{
	TWSR = 0X00;		// set prescaler bits to zero
	TWCR = 0X04;		// enable the TWI module (two wire serial interrupt)
	TWBR = 0X47;		// set the clock frequency to 50k for 8M crystal
}



#endif