#include "bitmask.hpp"

Bitmask::Bitmask()
: bitmask_(), width_(0), height_(0)
{
	
}
Bitmask::Bitmask(int w, int h)
: bitmask_(), width_(w), height_(h)
{
	bitmask_.resize((h * ((w - 1) / BIT_LENGTH_ + 1)),0);
}

int Bitmask::mask(int n) const
{
	return 1 << (n & BIT_MASK_);
}

void Bitmask::set_bit(int x, int y)
{
	bitmask_[(x / BIT_LENGTH_* height_ + y)] |= mask(x);
}
	
bool Bitmask::get_bit(int x, int y) const
{	
	if ((bitmask_[(x/BIT_LENGTH_ * height_ + y)] & mask(x)) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Bitmask::overlaps(Bitmask& b, int x_offset, int y_offset)
{
	Bitmask& a = *this;
	
	if ((x_offset >= a.width_) || (y_offset >= a.height_) || (y_offset <= - b.height_))
	{
		return false;
	}
	while (true)
	{
		if (x_offset >= 0) 
		{
			int a_entry;
			int a_end;
			int b_entry;
			
			if (y_offset >= 0) 
			{
				a_entry = a.height_ * (x_offset / BIT_LENGTH_) + y_offset;
				a_end = a_entry + std::min(b.height_, a.height_ - y_offset);
				b_entry = 0;
			}
			else 
			{
				a_entry = a.height_ * (x_offset / BIT_LENGTH_);
				a_end = a_entry + std::min(b.height_ + y_offset, a.height_);
				b_entry = -y_offset;
			}
			
			int shift = x_offset & BIT_MASK_;
			
			if (shift != 0) 
			{
				const int rshift = BIT_LENGTH_ - shift;
				const int astripes = ((a.width_ - 1)) / BIT_LENGTH_ - x_offset / BIT_LENGTH_;
				const int bstripes = ((b.width_ - 1)) / BIT_LENGTH_ + 1;
				
				if (bstripes > astripes)
				{
					for (int i = 0; i < astripes; i++)
					{
						for (int ap = a_entry, app = ap + a.height_, bp = b_entry; ap < a_end;) 
						{
							if (((a.bitmask_[ap++] >> shift) & b.bitmask_[bp]) != 0
								|| ((a.bitmask_[app++] << rshift) & b.bitmask_[bp++]) != 0) 
							{
								return true;
							}
						}
						
						a_entry += a.height_;
						a_end += a.height_;
						b_entry += b.height_;
					}
					for (int ap = a_entry, bp = b_entry; ap < a_end;) {
							if (((a.bitmask_[ap++] >> shift) & b.bitmask_[bp++]) != 0) {
								return true;
							}
					}
					return false;
				}
				for (int i = 0; i < bstripes; i++) {
						for (int ap = a_entry, app = ap + a.height_, bp = b_entry; ap < a_end;) {
							if (((a.bitmask_[ap++] >> shift) & b.bitmask_[bp]) != 0
									|| ((a.bitmask_[app++] << rshift) & b.bitmask_[bp++]) != 0) {
								return true;
							}
						}
						a_entry += a.height_;
						a_end += a.height_;
						b_entry += b.height_;
				}
				return false;
			}
			
			const int astripes = (std::min(b.width_, a.width_ - x_offset) - 1) / BIT_LENGTH_ + 1;
			
			for (long i = 0; i < astripes; i++) {
					for (long ap = a_entry, bp = b_entry; ap < a_end;) {
						if ((a.bitmask_[ap++] & b.bitmask_[bp++]) != 0) {
							return true;
						}
					}
					a_entry += a.height_;
					a_end += a.height_;
					b_entry += b.height_;
			}
			return false;
		}
		Bitmask& c = a;
		a = b;
		b = c;
		x_offset *= -1;
		y_offset *= -1;
	}
}
