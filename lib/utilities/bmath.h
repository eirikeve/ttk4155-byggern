namespace bmath
{
    
    template<typename Number>
    Number abs(Number i)
    {
        try
        {
            if (i < 0)
            {
                return -i;
            }
            return i;
        } catch() {return i;}
        
    }
}

