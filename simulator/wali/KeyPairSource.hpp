#ifndef wali_KEY_PAIR_SOURCE_GUARD
#define wali_KEY_PAIR_SOURCE_GUARD 1

/**
 * @author Nicholas Kidd
 */

#include "Common.hpp"
#include "KeySource.hpp"
#include "KeyContainer.hpp"

namespace wali
{
  class KeyPairSource : public wali::KeySource
  {
    public:
      KeyPairSource( Key k1, Key k2 );

      KeyPairSource( const KeyPair& kp );

      virtual ~KeyPairSource();

      virtual bool equal( KeySource* rhs );

      virtual size_t hash() const;

      virtual std::ostream& print( std::ostream& o ) const;

      const KeyPair& get_key_pair() const;

      Key first() const;

      Key second() const;

      static Key get_first(Key k);
      static Key get_second(Key k);

    private:
      const KeyPair kp;

  }; // class KeyPairSource

} // namespace wali

#endif  // wali_KEY_PAIR_SOURCE_GUARD

