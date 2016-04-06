/*
 * testiranje.h
 *
 * Created: 16/11/15 14:36:33
 *  Author: marko
 */ 


#ifndef TESTIRANJE_H_
#define TESTIRANJE_H_

char proveri_poziciju(void);
void postavi_koordinatni_sistem(signed long x, signed long y, signed long teta_des);
void nuliraj_poziciju_robota(void);
void zadaj_X_Y_teta(signed long x, signed long y, signed long teta_des, unsigned char dir);
void zadaj_X_Y(signed long x, signed long y, unsigned char dir);
void zadaj_teta(signed long teta_des);

void inicijalizuj_bluetooth();
void posalji_poruku_bt(char *poruka);
void posalji_karakter_bt(char c);

void inicijalizuj_servo_tajmer_20ms();
void pomeri_servo_1(uint16_t deg);
void pomeri_servo_2(uint16_t deg);
void pomeri_servo_3(uint16_t deg);
void pomeri_servo_4(uint16_t deg);

void otvori_hvataljku(void);
void otvori_hvataljku_vise(void);
void zatvori_hvataljku(void);
void zatvori_hvataljku_pola(void);
void otvori_lepezu(void);
void zatvori_lepezu(void);

void izvuci_cilindar(void);
void uvuci_cilindar(void);

void spusti_zvono(void);
void podigni_zvono(void);

void kombinacija1pink(void);
void kombinacija2pink(void);
void kombinacija3pink(void);
void kombinacija4pink(void);
void kombinacija5pink(void);

void kombinacija1green(void);
void kombinacija2green(void);
void kombinacija3green(void);
void kombinacija4green(void);
void kombinacija5green(void);

#endif /* TESTIRANJE_H_ */