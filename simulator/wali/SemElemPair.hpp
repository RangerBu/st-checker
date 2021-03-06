#ifndef wali_SEMELEM_PAIR_GUARD
#define wali_SEMELEM_PAIR_GUARD 1

/**
 * @author Nicholas Kidd
 */

#include "Common.hpp"
#include "SemElem.hpp"

namespace wali
{
  class SemElemPair : public SemElem
  {
    public:
      SemElemPair( SemElem* fst, SemElem* snd );

      SemElemPair( sem_elem_t fst, sem_elem_t snd );

      virtual ~SemElemPair();

      /** @brief return the One element of the semiring */
      virtual sem_elem_t one() const;

      /** @brief return the Zero element of the semiring */
      virtual sem_elem_t zero() const;

      /** @brief Perform the extend operation */
      virtual sem_elem_t extend( SemElem * se );

      /** @brief Perform the combine operation */
      virtual sem_elem_t combine( SemElem * se );

      /** @brief Equality comparison between two semiring elements */
      virtual bool equal( SemElem * se ) const;

      /** @brief Print the semiring element to the std::ostream o */
      virtual std::ostream& print( std::ostream & o ) const;

      /** @brief Perform the diff operation */
      virtual sem_elem_t diff( SemElem * se );

      /** @brief Perform the quasi_one operation */
      virtual sem_elem_t quasi_one() const;

      /** @brief Perform the delta operation */
      virtual std::pair<sem_elem_t,sem_elem_t> delta( SemElem * se );

      /** @brief return first element */
      sem_elem_t getFirst() const {
        return first; 
      }

      /** @brief return second element */
      sem_elem_t getSecond() const {
        return second; 
      }

      /** @brief return first element */
      sem_elem_t get_first() const {
        return first; 
      }

      /** @brief return second element */
      sem_elem_t get_second() const {
        return second; 
      }


      size_t hash() const {
        // Wikipedia's entry for the Java hashcode() function recommends
        // basically a + 17*b + 17*31*c, but I'll skip the b step.
        return get_first()->hash() + (17*31) * get_second()->hash();
      }
      

      virtual
      std::ostream &
      print_typename(std::ostream & os) const {
          os << "pair<";
          first->print_typename(os) << ", ";
          second->print_typename(os) << ">";
          return os;
      }

    protected:
      sem_elem_t first;
      sem_elem_t second;

  }; // class SemElemPair

} // namespace

#endif  // wali_SEMELEM_PAIR_GUARD

