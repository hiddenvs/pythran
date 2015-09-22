#ifndef PYTHONIC_INCLUDE_NUMPY_NDENUMERATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDENUMERATE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/numpy_type.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    struct ndenumerate_iterator
        : std::iterator<
              std::random_access_iterator_tag,
              std::tuple<
                  types::array<long, types::numpy_expr_to_ndarray<E>::N>,
                  typename types::numpy_expr_to_ndarray<E>::type::dtype>> {
      long index;
      E const &expr;
      typename types::numpy_expr_to_ndarray<E>::type::dtype *iter;

      ndenumerate_iterator();
      ndenumerate_iterator(E const &expr, long first);

      std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>,
                 typename types::numpy_expr_to_ndarray<E>::type::dtype>
      operator*();

      ndenumerate_iterator &operator++();
      ndenumerate_iterator &operator+=(long n);
      bool operator!=(ndenumerate_iterator const &other);
      bool operator<(ndenumerate_iterator const &other);
      long operator-(ndenumerate_iterator const &other);
    };

    template <class E>
    struct _ndenumerate : ndenumerate_iterator<E> {
      using iterator = ndenumerate_iterator<E>;
      E expr; // we need to keep one ref over the enumerated sequence alive
      iterator end_iter;

      _ndenumerate();
      _ndenumerate(E const &expr);
      iterator &begin();
      iterator const &begin() const;
      iterator end() const;
    };

    template <class T, size_t N>
    _ndenumerate<types::ndarray<T, N>>
    ndenumerate(types::ndarray<T, N> const &expr);

    NUMPY_EXPR_TO_NDARRAY0_DECL(ndenumerate);
    PROXY_DECL(pythonic::numpy, ndenumerate);
  }
}

#endif
