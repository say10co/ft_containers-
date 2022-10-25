#ifndef iterator_traits_HPP  
#define iterator_traits_HPP 

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	
	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <bool is_const, typename const_type, typename non_const_type>
	struct deduce;

	template <typename const_type, typename non_const_type>
	struct deduce<true, const_type, non_const_type>
	{
		typedef const_type type;
	};

	template <typename const_type, typename non_const_type>
	struct deduce<false, const_type, non_const_type>
	{
		typedef non_const_type type;
	};

};

#endif //2iterator_traits_HPP
