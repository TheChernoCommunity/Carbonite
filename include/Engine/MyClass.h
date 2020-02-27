#pragma once

class MyClass
{
public:

	MyClass( int value );

public:

	int Value( void ) const { return value_; }

private:

	int value_;

};
