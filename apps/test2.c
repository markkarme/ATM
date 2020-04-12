/*
 * Test.c
 *
 *  Created on: Oct 16, 2019
 *      Author: Marktronix
 */
/*this is a code for ATM
 *the ATM deal with superadmin , admin and user
 *for every one have id and password
 *the password and id must be in 4 digit
 *the user have 3 time to enter worng
 *the admin have 3 time to enter worng
 *the superadmin have 8 time to enter worng
 *the admin has the capability to add aother admin and user
 *the superadmin has the capability to add aother superadmin and admin
 */
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include "../utils/custom_types.h"
#include "../hal/lcd/lcd.h"
#include "../mcal/DIO/Dio.h"
#include"../hal/keypad/keypad.h"
#include "../mcal/usart/usart.h"
#define first_address_of_user_in_hex 0x60
#define last_address_of_user_in_hex 0x99

#define first_address_of_user 60
#define last_address_of_user 99

#define first_address_of_admin_in_hex 0x20
#define last_address_of_admin_in_hex 0x59

#define first_address_of_admin 20
#define last_address_of_admin 59

#define first_address_of_superadmin 0x0
#define last_address_of_superadmin 0x16

//#define first_address_of_superadmin2 0x08

#define last_index_user 0x200
#define last_index_admin 0x300
#define last_index_superadmin 0x350

void user();
void admin();
void superadmin();
void addpesron(u8_t thelastadress ,u8_t name[]);
u8_t check_id1(u8_t first_address_eeprom,u8_t secound_address_eeprom);
u8_t check_password1(u8_t first_address_eeprom,u8_t secound_address_eeprom);
void check_person(u8_t checkid3,u8_t checkpassword3,u8_t person);
void addressesofeeprom();
void motor_run();


void test2(void)
{
	init_usart(9600);
	init_keypad();
	init_lcd();
	dio_channel_config(Dio_channel_c3,output);
	dio_channel_config(Dio_channel_c4,output);
	//if(EEPROM_read(last_index_superadmin)!=0x08)
	/*here you should build the code the upload the code the make a comment in the next line */
	addressesofeeprom();
	/*after you make a comment make build again and upload the code again thanke*/
	usart_write_text("          HELLO AT YOUR ATM              ") ;
	lcd_write_text("welcom ",1,1);
	while(1)
	{
		usart_write_text("\n\r if you are user enter 1");
		usart_write_text("\n\r if you are admin enter 2");
		usart_write_text("\n\r if you are usperadmin enter 3");
		u8_t answer=get_key_clicked();
		switch(answer)
		{
			case '1':
			user();
			break;
			case '2':
			admin();
			break;
			case '3':
			superadmin();
			break;
			default:
			usart_write_text("\n\r enter 1 or 2 or 3");
			test2();
			break;
		}
	}
}
void user()
{
	u8_t checkid,checkpass;
	checkid=check_id1(first_address_of_user,last_address_of_user);
	checkpass=check_password1(first_address_of_user,last_address_of_user);
	check_person(checkid,checkpass,'1');
}
void admin()
{
	u8_t checked_id,checked_password,answer,answer2;
	u16_t last_address=0;
	checked_id=check_id1(first_address_of_admin,last_address_of_admin);
	checked_password=check_password1(first_address_of_admin,last_address_of_admin);
	check_person(checked_id,checked_password,'2');
	do{
		usart_write_text("\n\r if you want to add user press 1");
		usart_write_text("\n\r if you want to add admin press 2");
		usart_write_text("\n\r if you want do nothing press any key rather than 1,2 ");
		answer=get_key_clicked();
		if(answer=='1')
		{
			last_address=EEPROM_read(last_index_user);
			addpesron(last_address,"user");
		}else if(answer =='2')
		{
			last_address=EEPROM_read(last_index_admin);
			addpesron(last_address,"admin");
		}else
		{
			break;
		}
		usart_write_text("\n\r if you want to try again perss 5 else press any key");
		answer2=get_key_clicked();
	}while(answer2 =='5');
}
void superadmin()
{

	u8_t checked_id,checked_password,answer,answer2;
	u16_t last_address;
	checked_id=check_id1(first_address_of_superadmin,last_address_of_superadmin);
	checked_password=check_password1(first_address_of_superadmin,last_address_of_superadmin);
	check_person(checked_id,checked_password,'3');
	do
	{
		usart_write_text("\n\r if you want to add superadmin press 1");
		usart_write_text("\n\r if you want to add admin press 2");
		usart_write_text("\n\r if you want do nothing press any key rather than 1,2 ");
		lcd_write_text("press 2",1,1);
		u8_t answer=get_key_clicked();
		if(answer=='1')
		{
			last_address=EEPROM_read(last_index_superadmin);
			addpesron(last_address,"super admin");
		}else if(answer =='2')
		{
			last_address=EEPROM_read(last_index_admin);
			addpesron(last_address,"admin");
		}else
		{
			break;
		}
		usart_write_text("\n\r if you want to try again perss 5 else press any key");
		answer2=get_key_clicked();
	}while(answer2=='5');
}
void addpesron(u8_t thelastadress ,u8_t name[])
{

	if(name[0]=='s' && EEPROM_read(last_index_superadmin)!= 0x16)
	{
		usart_write_text("\n\r sorry you can't add superadmin");
		u8_t answer;
		usart_write_text("\n\r if you want to try again perss 5 else press any key");
		answer=get_key_clicked();
		if(answer=='5')
		{
			superadmin();
		}
	}
	u8_t new_id[4],i=0;
	u8_t new_password[4],z=0;
	lcd_clear();
	usart_write_text("\n\r add the new id of");
	usart_write_text(name);
	lcd_write_text("enter id ",1,1);
	new_id[0]=get_key_clicked();
	lcd_write_char('*',2,1);

	while(new_id[i]!='D')
	{
		new_id[++i]=get_key_clicked();
		lcd_write_char_cp('*');

	}
	for(i=thelastadress;i<thelastadress+4;i++)
	{
		EEPROM_write(i,new_id[z]);
		z++;
	}
	z=0;
	i=0;
	usart_write_text("\n\r add the of new password ");
	usart_write_text(name);

	lcd_clear();
	lcd_write_text("enter pass",1,1);
	new_password[0]=get_key_clicked();
	lcd_write_char('*',2,1);
	while(new_password[i]!='D')
	{
		new_password[++i]=get_key_clicked();
		lcd_write_char_cp('*');
	}
	for(i=thelastadress+4;i<thelastadress+8;i++)
	{
		EEPROM_write(i,new_password[z]);
		z++;
	}
	if(name[0]=='u')
	{
		EEPROM_write(last_index_user,thelastadress+8);
	}else if(name[0] == 'a')
	{
		EEPROM_write(last_index_admin,thelastadress+8);
	}else if(name[0] == 's')
	{
		EEPROM_write(last_index_superadmin,thelastadress+8);
	}
}
void addressesofeeprom()
{
	u8_t x=0,i=0;
	u8_t superadmin_id_and_pass[16]={'1','2','3','4','5','6','7','8','5','4','3','2','6','7','8','9'};

	for( i=0;i<16;i++)
	{
		EEPROM_write(i,superadmin_id_and_pass[i]);
	}
	EEPROM_write(last_index_admin,first_address_of_admin_in_hex);
	EEPROM_write(last_index_user,first_address_of_user_in_hex);
	EEPROM_write(last_index_superadmin,0x08);

}

u8_t check_id1(u8_t first_address_eeprom,u8_t secound_address_eeprom)
{
	u8_t login_id[4],x=first_address_eeprom,z=0,i=0,counter=0;
	if(first_address_eeprom == first_address_of_user)
	{
		x=first_address_of_user_in_hex;

	}else if(first_address_eeprom == first_address_of_admin)
	{
		x=first_address_of_admin_in_hex;

	}

	usart_write_text("\n\r enter your id ");
	lcd_clear();
	lcd_write_text("enter id",1,1);
	login_id[i]=get_key_clicked();
	lcd_write_char('*',2,1);
	while(login_id[i]!='D')
	{
		login_id[++i]=get_key_clicked();
		lcd_write_char_cp('*');
	}
	for(i=first_address_eeprom;i<=secound_address_eeprom;i++)
	{
		if(i%5)
		{

			if(EEPROM_read(x)==login_id[z])
			{
				counter=counter+1;
				if(counter==4)
				{
					break;
				}else
				{

			    }
				}else
				{
					counter=counter-1;
				}
				z++;
				x++;
		}else
		{
			z=0;
			counter=0;
		}
	}

	return counter;
}

u8_t check_password1(u8_t first_address_eeprom,u8_t secound_address_eeprom)
{
	u8_t login_id[4],x=first_address_eeprom,z=0,i=0,counter=0;
	if(first_address_eeprom == first_address_of_user)//here there is a ; that made me rolling
	{
		x=first_address_of_user_in_hex;
	}else if(first_address_eeprom == first_address_of_admin)
	{
		x=first_address_of_admin_in_hex;

	}
	usart_write_text("\n\r enter your password");
	lcd_clear();
	lcd_write_text("enter pasword",1,1);
	login_id[i]=get_key_clicked();
	lcd_write_char('*',2,1);
	while(login_id[i]!='D')
	{
		login_id[++i]=get_key_clicked();
		lcd_write_char_cp('*');

	}
	for(i=first_address_eeprom;i<secound_address_eeprom;i++)
	{
		if(i%5)
		{
			if(EEPROM_read(x)==login_id[z])
			{
				counter=counter+1;
				if(counter==4)
				{
					break;
				}else
				{

			    }
				}else
				{
					counter=counter-1;
				}
				z++;
				x++;
		}else
		{
			z=0;
			counter=0;
		}
	}

	return counter;
}
void check_person(u8_t checkid3,u8_t checkpassword3,u8_t person)
{
	static u8_t counter=0,x=0;
	if(x==0)
	{
		if(person=='1')
		{
			counter=0;
		}else if(person=='2')
		{
			counter=4;

		}else if(person =='3')
		{
			counter=8;
		}
	}
	if(checkid3 ==4  && checkpassword3==4)
	{
		if(person=='2' || person =='3')
		{
			usart_write_text("\n\r welcom");
		}else
		{
			motor_run();
			usart_write_text("\n\r welcom");
		}

	}else
	{
		counter++;
		if(counter<4)
		{
			user();
		}else if(counter>=4 && counter<8 )
		{
			x=1;
			usart_write_text("\n\r system locked");
			admin();
		}else if(counter>=8 && counter<=16)
		{
			x=1;
			usart_write_text("\n\r system turns into super lock mood");
			superadmin();
		}else if(counter>16)
		{
			usart_write_text("\n\r system completely  close");
			while(1);

		}
	}
}
void motor_run()
{

	dio_channel_set(Dio_channel_c3,high);
	dio_channel_set(Dio_channel_c4,low);
	_delay_ms(1000);
	dio_channel_set(Dio_channel_c3,low);
	dio_channel_set(Dio_channel_c4,low);

}

