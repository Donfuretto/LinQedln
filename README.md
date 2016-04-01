# LinQedln
Versione c++ del sistema linkedln
----------------------------------
Il progetto LinQedln consiste nel ricreare un ambiente con le principali
funzionalità di Linkedln sviluppato in Qt.
La gestione delle notifiche e news è stato ignorato per questioni pratiche.
Come amministratore è possibile tramite interfaccia, gestire il database e le
caratteristiche del singolo utente, caricare un nuovo database oppure farne
il backup, aggiungere ed eliminare utenti ed apportare eventuali modifiche
al profilo.
Come utente è possibile gestire il proprio account, visualizzare la rete di
contatti secondo le metodologie social e visualizzare le loro informazioni.
Il salvataggio è automatico, quindi ogni modifica amministrativa è
significativa, in caso di errore è possibile caricare un backup del database.
Per la grafica si è cercato di seguire il pattern MVC. La GUI è stata scritta
senza l’ausilio di QtDesigner, in modo da poter approfondire il più possibile
le dinamiche di funzionamento delle librerie grafiche di Qt-Widget.
