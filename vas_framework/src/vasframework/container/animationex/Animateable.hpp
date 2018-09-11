namespace vas
{
	struct Animateable
	{
		virtual void tick() = 0;
		virtual bool done() = 0;
	};
}