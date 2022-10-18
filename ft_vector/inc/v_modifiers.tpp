
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
				(this->_allocator).construct(advance_by(new_ptr, i++ * sizeof(value_type)), *it);
			ft_distroy(this->_m_data, this->_allocator, this->_size);
			(this->_allocator).deallocate(this->_m_data, this->_capacity); // Old capacity  
			this->_m_data = new_ptr;
			this->_capacity = capacity;
			return ;
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
typename ft_vector<type, Alloc>::iterator ft_vector<type, Alloc>::insert (iterator position, const value_type& val)
{
	size_type distance = position - this->_m_data;
	this->insert(position, 1, val);
	return (iterator(this->_m_data + distance));
}

template<class type, class Alloc>
void ft_vector<type, Alloc>::insert (iterator position, size_type n, const value_type& val)
{
	ft_vector tmp(n, val);
	this->insert(position, tmp.begin(), tmp.end());

}

template<class type, class Alloc>
template <class InputIterator>
void ft_vector<type, Alloc>::insert (iterator position, InputIterator first, InputIterator last,
		typename  enable_if<!is_integral<InputIterator>::value, InputIterator>::type*)
{

	iterator tmp_first = first;
	size_type nb_elements = 0;
	pointer new_ptr;

	iterator it = this->begin();
	iterator ite = this->end();
	size_type index = 0;

	while (tmp_first != last)
	{
		tmp_first++;
		nb_elements++;
	}
	size_type total_size  = this->_size + nb_elements;
	
	if (this->_size + nb_elements > this->_capacity) // reallocation needed 
	{
		new_ptr = (this->_allocator).allocate(total_size);

		for (;it != position; it++, index++) 
			(this->_allocator).construct(new_ptr + index, *it);
		for (;first != last; first++,  index++)
			(this->_allocator).construct(new_ptr + index, *first);
		for (;it != ite; it++, index++)
			(this->_allocator).construct(new_ptr + index, *it);

		ft_distroy(this->_m_data, this->_allocator, this->_size);
		this->_m_data = new_ptr;
		this->_capacity = total_size;
	}
	else
	{
		// Copeing overwridden elements 
		//std::cout << "before copy " << std::endl;
		ft_vector copy(*this);

		index = position - this->_m_data; 
		it = copy.begin() + index;
		ite = copy.end();

		for(; first != last; first++, index++)
		{
			(this->_allocator).destroy(this->_m_data + index);
			(this->_allocator).construct(this->_m_data + index, *first);
		}
		
		// restorting element after insert 
		for (; it != ite; it++, index++)	
		{
			(this->_allocator).destroy(this->_m_data + index);
			(this->_allocator).construct(this->_m_data + index, *it);
		}
	}
	this->_size += nb_elements;
}
