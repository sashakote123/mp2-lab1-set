#include "tbitfield.h"

using namespace std;



TBitField::TBitField(int len):BitLen(len) {
	if (len < 0) 
		throw exception();
	else {
		if (len % (sizeof(uint) * 8) == 0)
			MemLen = len / (sizeof(uint) * 8);
		if (len % (sizeof(uint) * 8) != 0)
			MemLen++;
		pMem = new uint[MemLen];
		for (size_t i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf):BitLen(bf.BitLen) { // конструктор копирования
	MemLen = bf.MemLen;
	pMem = new uint[MemLen];
	for (size_t i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() {
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
	if (n < 0 || n >= BitLen)
		throw exception();
	return (n / (sizeof(uint) * 8));
}

uint TBitField::GetMemMask(const int n) const { // битовая маска для бита n
	if (n < 0 || n>BitLen)
		throw exception();
	return (1 << (n % (sizeof(uint) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const { // получить длину (к-во битов)
	return BitLen;
}

void TBitField::SetBit(const int n) { // установить бит
	if (n < 0 || n >= BitLen)
		throw exception();
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) { // очистить бит
	if (n < 0 || n >= BitLen)
		throw exception();
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const{ // получить значение бита
	if (n < 0 || n >= BitLen)
		throw exception();
	return pMem[GetMemIndex(n)] & GetMemMask(n) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) { // присваивание

	if (this == &bf)
		return *this;

	uint* pMem2 = new uint[bf.MemLen];
	delete[] pMem;
	pMem = pMem2;

	MemLen = bf.MemLen;
	BitLen = bf.BitLen;

	for (size_t i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	
	return *this;
}

int TBitField::operator==(const TBitField& bf) const { // сравнение
	if (bf.BitLen != BitLen)
		return 0;
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const{ // сравнение
	return !(bf == *this);
}

TBitField TBitField::operator|(const TBitField& bf) { // операция "или"
	TBitField tmp(BitLen);
	for (size_t i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	return tmp;

}

TBitField TBitField::operator&(const TBitField& bf) { // операция "и"
	TBitField tmp(BitLen);
	for (size_t i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] = bf.pMem[i] & pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) { // отрицание
	TBitField tmp(BitLen);
	for (size_t i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) { // ввод
	for (size_t i = 0; i < bf.GetLength(); i++) {
		int qwe;
		istr >> qwe;
		bf.SetBit(i);
		if (qwe == 0)
			bf.ClrBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) {  // вывод
	for (size_t i = 0; i < bf.GetLength(); i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}
