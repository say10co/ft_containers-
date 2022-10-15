
template <class type, class Alloc>
template <class InputIterator>
void ft_vector<type, Alloc>::assign (InputIterator first, InputIterator last)
{
	size_type size = last - first;  
	std::cout << size << std::endl;
	ft_distroy(this->_m_data, this->_allocator, this->_size);

	if (size > this->_capacity)
	{
		(this->_allocator).deallocate(this->_m_data, this->_capacity);
		this->_m_data = (this->_allocator).allocate(size);
		this->_capacity = size;
	}
	this->_size = size;
	for (size_type i = 0; i < size ; i++)
	{
		(this->_allocator).construct(advance_by(this->_m_data, i *sizeof(value_type)), *first++);
	}
}
template<class type, class Alloc>
void ft_vector<type, Alloc>::push_back (const value_type& val)
{
		if (this->_size >= this->_capacity)	
		{
			size_type capacity = (this->_capacity) == 0 ? 1 : this->_capacity * 2 ;
			pointer new_ptr = (this->_allocator).allocate(capacity);
			int	i = 0;
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				std::cout << "it value :" << *it << std::endl;
				(this->_allocator).construct(advance_by(new_ptr, i++ * sizeof(value_type)), *it);
		}
			ft_distroy(this->_m_data, this->_allocator, this->_size);
			(this->_allocator).deallocate(this->_m_data, this->_capacity); // Old capacity  
			this->_m_data = new_ptr;
			this->_capacity = capacity;
		}
		(this->_allocator).construct(advance_by(this->_m_data, this->_size * sizeof(value_type)), val);
		this->_size += 1;
}
 
template<class type, class Alloc>
void ft_vector<type, Alloc>::pop_back()
{
	(this->_allocator).destroy(advance_by(this->_m_data, this->_size - 1));
	this->_size--;
}

template<class type, class Alloc>
typename ft_vetor<type, Alloc>::iterator ft_vector<type, Alloc>::insert (iterator position, const value_type& val);
{
	size_type size;
	
}


