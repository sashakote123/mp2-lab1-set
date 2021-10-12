#include "tbitfield.h"


TBitField::TBitField(int len) {
	MemLen = len / (sizeof(uint) * 8);
	pMem = new uint[MemLen];
	for (size_t i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) { // конструктор копирования
	MemLen = bf.MemLen;
	pMem = new uint[MemLen];
	for (size_t i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() {
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
	return n / (sizeof(uint) * 8);
}

uint TBitField::GetMemMask(const int n) const { // битовая маска для бита n
	return (1 << (n % (sizeof(uint) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const { // получить длину (к-во битов)
	return BitLen;
}

void TBitField::SetBit(const int n) { // установить бит
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] + pMem[GetMemMask(n)];
}

void TBitField::ClrBit(const int n) { // очистить бит
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] - pMem[GetMemMask(n)];
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return pMem[GetMemIndex(n)] & pMem[GetMemMask(n)];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) { // присваивание
	//MemLen = bf.MemLen;
	//BitLen = bf.BitLen;

	TBitField tmp(bf);
	swap(pMem, tmp.pMem);

	return *this;

}

int TBitField::operator==(const TBitField& bf) const { // сравнение
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) { // операция "или"
	TBitField tmp(BitLen);
	for (size_t i = 0; i < bf.GetLength(); i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	return tmp;

}

TBitField TBitField::operator&(const TBitField& bf) { // операция "и"
	TBitField tmp(BitLen);
	for (size_t i = 0; i < bf.GetLength(); i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
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
