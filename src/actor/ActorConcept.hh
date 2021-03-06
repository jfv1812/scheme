#ifndef INCLUDED_actor_ActorConcept_HH
#define INCLUDED_actor_ActorConcept_HH



namespace scheme {
namespace actor {




	template<class _Position, class _Data>
	struct ActorConcept {

		typedef _Position Position;
		typedef _Data Data;
		typedef ActorConcept<Position,Data> THIS;

		Position position_;
		Data data_;

		ActorConcept() : position_(), data_() {}

		ActorConcept(Position const & p, Data const & d) : position_(p), data_(d) {}

		ActorConcept(
			ActorConcept const & actor0,
			Position const & moveby
		){
			data_ = actor0.data_;
			set_position(moveby*actor0.position());
		}

		void 
		set_position(
			Position const & pos
		){ position_ = pos; }

		Position const &
		position() const { return position_; }

		bool operator==(THIS const & o) const { return o.position_==position_ && o.data_==data_; }
	};


}
}

#endif
