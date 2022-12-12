#include "Primitive.h"

const Matrix34 Primitive::getOffset() const
{
    return m_offset;
}

void Primitive::setOffset(Matrix34 _offset)
{
    m_offset = _offset;
}

std::string Primitive::getShape() const
{
    return "";
}
