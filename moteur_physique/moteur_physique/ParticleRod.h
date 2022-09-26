class ParticleRod: public ParticleLink
public:
// a contact will be genereated if the distance / between particles is not equal to the length.
float length;
// Fill ParticleContact with information from particles and contact generator.
// Contact is different wether the distance is shorter or greater then the length
unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};
