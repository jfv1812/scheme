
#include <nest/maps/SphereQuad.hh>
#include <nest/NEST.hh>
#include <nest/NEST_concepts.hh>
#include <nest/NEST_test_util.hh>
#include <gtest/gtest.h>
#include <boost/random.hpp>

namespace scheme {
namespace nest {
namespace maps {

using std::cout;
using std::endl;

TEST( SphereQuad, cell_centers ){
	typedef SphereQuad<2,util::SimpleArray<3,double> > MapType;
	typedef MapType::Params PRM;
	typedef MapType::ValueType VAL;
	MapType sd;
	PRM prm;
	VAL val;
	size_t celli;

	sd.params_to_value( PRM(0.5,0.5), 0, val ); ASSERT_EQ( val, VAL( 0, 0, 1) );
	sd.params_to_value( PRM(0.5,0.5), 1, val ); ASSERT_EQ( val, VAL( 0, 1, 0) );
	sd.params_to_value( PRM(0.5,0.5), 2, val ); ASSERT_EQ( val, VAL(-1, 0, 0) );
	sd.params_to_value( PRM(0.5,0.5), 3, val ); ASSERT_EQ( val, VAL( 0,-1, 0) );
	sd.params_to_value( PRM(0.5,0.5), 4, val ); ASSERT_EQ( val, VAL( 1, 0, 0) );
	sd.params_to_value( PRM(0.5,0.5), 5, val ); ASSERT_EQ( val, VAL( 0, 0,-1) );

	sd.value_to_params( VAL( 0, 0, 1), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 0 );
	sd.value_to_params( VAL( 0, 1, 0), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 1 );
	sd.value_to_params( VAL(-1, 0, 0), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 2 );
	sd.value_to_params( VAL( 0,-1, 0), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 3 );
	sd.value_to_params( VAL( 1, 0, 0), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 4 );
	sd.value_to_params( VAL( 0, 0,-1), prm, celli ); ASSERT_EQ( prm, PRM(0.5,0.5) ); ASSERT_EQ( celli, 5 );

	sd.value_to_params( VAL( 0.999999999, 0.999999999, 1.000000000), prm, celli ); ASSERT_EQ( celli, 0 );
	sd.value_to_params( VAL( 0.999999999, 1.000000000, 0.999999999), prm, celli ); ASSERT_EQ( celli, 1 );
	sd.value_to_params( VAL(-1.000000000, 0.999999999, 0.999999999), prm, celli ); ASSERT_EQ( celli, 2 );
	sd.value_to_params( VAL( 0.999999999,-1.000000000, 0.999999999), prm, celli ); ASSERT_EQ( celli, 3 );
	sd.value_to_params( VAL( 1.000000000, 0.999999999, 0.999999999), prm, celli ); ASSERT_EQ( celli, 4 );
	sd.value_to_params( VAL( 0.999999999, 0.999999999,-1.000000000), prm, celli ); ASSERT_EQ( celli, 5 );

	sd.value_to_params( VAL(-0.999999999, 0.999999999, 1.000000000), prm, celli ); ASSERT_EQ( celli, 0 );
	sd.value_to_params( VAL(-0.999999999, 1.000000000, 0.999999999), prm, celli ); ASSERT_EQ( celli, 1 );
	sd.value_to_params( VAL(-1.000000000,-0.999999999, 0.999999999), prm, celli ); ASSERT_EQ( celli, 2 );
	sd.value_to_params( VAL(-0.999999999,-1.000000000, 0.999999999), prm, celli ); ASSERT_EQ( celli, 3 );
	sd.value_to_params( VAL( 1.000000000,-0.999999999, 0.999999999), prm, celli ); ASSERT_EQ( celli, 4 );
	sd.value_to_params( VAL(-0.999999999, 0.999999999,-1.000000000), prm, celli ); ASSERT_EQ( celli, 5 );

	sd.value_to_params( VAL( 0.999999999,-0.999999999, 1.000000000), prm, celli ); ASSERT_EQ( celli, 0 );
	sd.value_to_params( VAL( 0.999999999, 1.000000000,-0.999999999), prm, celli ); ASSERT_EQ( celli, 1 );
	sd.value_to_params( VAL(-1.000000000, 0.999999999,-0.999999999), prm, celli ); ASSERT_EQ( celli, 2 );
	sd.value_to_params( VAL( 0.999999999,-1.000000000,-0.999999999), prm, celli ); ASSERT_EQ( celli, 3 );
	sd.value_to_params( VAL( 1.000000000, 0.999999999,-0.999999999), prm, celli ); ASSERT_EQ( celli, 4 );
	sd.value_to_params( VAL( 0.999999999,-0.999999999,-1.000000000), prm, celli ); ASSERT_EQ( celli, 5 );

	sd.value_to_params( VAL(-0.999999999,-0.999999999, 1.000000000), prm, celli ); ASSERT_EQ( celli, 0 );
	sd.value_to_params( VAL(-0.999999999, 1.000000000,-0.999999999), prm, celli ); ASSERT_EQ( celli, 1 );
	sd.value_to_params( VAL(-1.000000000,-0.999999999,-0.999999999), prm, celli ); ASSERT_EQ( celli, 2 );
	sd.value_to_params( VAL(-0.999999999,-1.000000000,-0.999999999), prm, celli ); ASSERT_EQ( celli, 3 );
	sd.value_to_params( VAL( 1.000000000,-0.999999999,-0.999999999), prm, celli ); ASSERT_EQ( celli, 4 );
	sd.value_to_params( VAL(-0.999999999,-0.999999999,-1.000000000), prm, celli ); ASSERT_EQ( celli, 5 );

	// sd.params_to_value( PRM(0.75,0.75), 5, val ); cout << val << endl;
	// sd.value_to_params( VAL( 1, 1, 1), prm, celli ); cout << prm.transpose() << " " << celli << endl;
}

TEST(SphereQuad,cell_boundaries){
	NEST<2,Vector3d,SphereQuad> nest;

	// edges
	ASSERT_EQ( nest.get_index(Vector3d( 0, 1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 0, 1,-1),0), 1 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 0,-1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 0,-1,-1),0), 3 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1, 0, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1, 0,-1),0), 4 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1, 0, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1, 0,-1),0), 2 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1, 1, 0),0), 1 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1,-1, 0),0), 3 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1, 1, 0),0), 1 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1,-1, 0),0), 2 ); // there go into the first cell they "touch"

	// corners
	ASSERT_EQ( nest.get_index(Vector3d( 1, 1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1, 1,-1),0), 1 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1,-1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d( 1,-1,-1),0), 3 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1, 1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1, 1,-1),0), 1 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1,-1, 1),0), 0 ); // there go into the first cell they "touch"
	ASSERT_EQ( nest.get_index(Vector3d(-1,-1,-1),0), 2 ); // there go into the first cell they "touch"
}

TEST( SphereQuad, test_index_nesting_of_bincenters ){
	generic_test_index_nesting_of_bincenters( NEST<2,Vector3d,SphereQuad>() , 6 );
	generic_test_index_nesting_of_value( NEST<2,Vector3d,SphereQuad>() , Vector3d(1,0,0), 6 );
	generic_test_index_nesting_of_value( NEST<2,Vector3d,SphereQuad>() , Vector3d(1,1,1), 6 );
}

TEST( SphereQuad, test_index_nesting_of_bincenters_various_valuetypes ){
	generic_test_index_nesting_of_bincenters( NEST<2,RowVector3d,SphereQuad>(), 3 );
	generic_test_index_nesting_of_bincenters( NEST<2,RowVector3f,SphereQuad>(), 3 );	
	generic_test_index_nesting_of_bincenters( NEST<2,   Vector3f,SphereQuad>(), 3 );		
	generic_test_index_nesting_of_bincenters( NEST<2,Array<double,3,1>,SphereQuad>(), 3 );	
	generic_test_index_nesting_of_bincenters( NEST<2,Array<double,1,3>,SphereQuad>(), 3 );	
	generic_test_index_nesting_of_bincenters( NEST<2,Array<float,1,3>,SphereQuad>(), 3 );	
	generic_test_index_nesting_of_bincenters( NEST<2,Array<float,1,3>,SphereQuad>(), 3 );	
	generic_test_index_nesting_of_bincenters( NEST<2,concept::ArrayValueArchitype<3>,SphereQuad>(), 3 );	
}

TEST(SphereQuad, test_coverage){
	typedef NEST<2,RowVector3d,SphereQuad> NestType;

	boost::random::mt19937 rng((unsigned int)time(0));
	boost::normal_distribution<> gaussian;
	
	size_t max_resl = 9;
	std::vector<double> largest_d2_for_r(max_resl+1,0.0);
	NestType nest;

	for(size_t i = 0; i < 100000; ++i){

		// set up random value within bounds
		NestType::ValueType val( gaussian(rng), gaussian(rng), gaussian(rng) );
		val = val / val.norm();

		// run generic coverage test
		generic_test_coverage_of_value( nest, val, largest_d2_for_r, max_resl );

	}
	for(size_t r = 0; r <= max_resl; ++r){
		// cout << r << " ratio: " << sqrt(largest_d2_for_r[r])/nest.bin_circumradius(r) << " largest delta: " << sqrt(largest_d2_for_r[r]) << " bin_circum: " << nest.bin_circumradius(r) << endl;
		// factor of 1.0+0.03*DIM is a *TOTAL* hack, errer does not scale this way by dimension
		// but it's enough to make sure the curcumradius is reasonably tight
		static double fudge[10] = { 1.3, 1.2, 1.15, 1.1, 1.09, 1.08, 1.08, 1.07, 1.06, 1.05 };
		if(  nest.bin_circumradius(r) > fudge[r]*sqrt(largest_d2_for_r[r]) ){
			cout << "WARNING(PROBABILISTIC): covering radius may be too loose SphereQuad Map, resl=" << r << endl;
			cout << "                        covering radius " << nest.bin_circumradius(r) << " max observerd: " << sqrt(largest_d2_for_r[r]) << endl;
			cout << "                        if you see a handful of these, don't worry. if you see lots, then worry" << endl;
		}
	}

}

}
}
}
