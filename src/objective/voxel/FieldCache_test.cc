#include <gtest/gtest.h>

#include "objective/voxel/FieldCache.hh"

#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/foreach.hpp>

#include <sstream>

namespace scheme { namespace objective { namespace voxel { namespace fctest {

using std::cout;
using std::endl;


struct Ellipse3D {
	static size_t ncalls;
	static double sqr(double f) { return f*f; }
	double c1,c2,c3,sd1,sd2,sd3;
	Ellipse3D() : c1(0),c2(0),c3(0),sd1(1),sd2(1),sd3(1) {}
	Ellipse3D(double a,double b,double c,double d,double e,double f) : c1(a),c2(b),c3(c),sd1(d),sd2(e),sd3(f) {}	
	double operator()(double f, double g, double h) const { 
		++ncalls;
		return 10.0+std::exp( -sqr((f-c1)/sd1) - sqr((g-c2)/sd2) - sqr((h-c3)/sd3) );
	}
	template<class F3> double operator()(F3 const & f3) const { return this->operator()(f3[0],f3[1],f3[2]); }
};
size_t Ellipse3D::ncalls = 0;

template<class Cache,class Field>
double test_cache_vs_field(Cache const & cache, Field field, int nsamp=10000){
	// cout << cache.num_elements()/1000000.0 <<"M" << endl;
	BOOST_STATIC_ASSERT(Cache::DIM==3);
	typedef util::SimpleArray<3,double> F3;
	boost::random::mt19937 rng((unsigned int)time(0));
	boost::uniform_real<> uniform;
	double maxerr = 0.0;
	for(int i = 0; i < nsamp; ++i){
		F3 samp = F3(uniform(rng),uniform(rng),uniform(rng)) * (cache.ub_-cache.lb_) + cache.lb_;
		double cacheval = cache[samp];
		double fieldval = field(samp);
		// std::cout << cacheval << " " << fieldval << std::endl;
		maxerr = std::max( std::abs(fieldval-cacheval), maxerr );
	}
	return maxerr;
}

TEST(FieldCache,test_accuracy_random){

	Ellipse3D field(1,2,3,4,5,6);
	ASSERT_FLOAT_EQ( field(1,2,3), 11.0 );

	ASSERT_LE( test_cache_vs_field( FieldCache3D<double>(field,-11,13,1.6), field, 100000 ), 0.30 );
	ASSERT_LE( test_cache_vs_field( FieldCache3D<double>(field,-11,13,0.8), field, 100000 ), 0.15 );
	ASSERT_LE( test_cache_vs_field( FieldCache3D<double>(field,-11,13,0.4), field, 100000 ), 0.08 );
	ASSERT_LE( test_cache_vs_field( FieldCache3D<double>(field,-11,13,0.2), field, 100000 ), 0.04 );

}

TEST(FieldCache,test_file_cache){
	std::string tmpfile = "FieldCache_test_file.bin.gz";
	 if(boost::filesystem::exists(tmpfile)) boost::filesystem::remove(tmpfile);

	Ellipse3D field(1,2,3,4,5,6);
	FieldCache3D<double> f1(field,-11,13,1.6,tmpfile);
	size_t ncalls = Ellipse3D::ncalls;

	FieldCache3D<double> f2(field,-11,13,1.6,tmpfile);

	ASSERT_EQ( Ellipse3D::ncalls, ncalls ); // field not called again
	ASSERT_EQ( f1 , f2 );

	f1.resize( util::SimpleArray<3,size_t>(0,0,0) ); // spoil the cache
	io::write_cache(tmpfile,f1);

	std::cout << "NOTE: the bounds-mismatch warning below is expected:" << std::endl;
	FieldCache3D<double> f3(field,-11,13,1.6,tmpfile);
	ASSERT_NE( Ellipse3D::ncalls, ncalls ); // field must be called again
	ASSERT_EQ( f2.shape()[0] , f3.shape()[0] );
	ASSERT_EQ( f2.shape()[1] , f3.shape()[1] );
	ASSERT_EQ( f2.shape()[2] , f3.shape()[2] );		
	ASSERT_EQ( f2 , f3 );


}

TEST(BoundingFieldCache,test_bounding){
	typedef util::SimpleArray<3,float> F3;
	Ellipse3D field(1,2,3,4,5,6);
	FieldCache3D<double> f1(field,-11,13,0.444);
	BoundingFieldCache3D<double> bf1(f1,2.0,0.812);

	cout <<  f1(F3(1,2,3)) << endl;
	cout << bf1(F3(1,2,3)) << endl;	

}


}}}}
