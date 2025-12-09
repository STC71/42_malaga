// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

/**
 * @title TournamentRegistry
 * @dev Stores immutable tournament results on Avalanche-compatible blockchain
 * @notice This contract provides transparent and tamper-proof tournament records
 */
contract TournamentRegistry {
    
    // Estructura para almacenar información de un torneo
    struct TournamentRecord {
        uint256 recordId;           // ID único del registro
        string tournamentName;      // Nombre del torneo
        uint256 startTime;          // Timestamp de inicio
        uint256 endTime;            // Timestamp de finalización
        address champion;           // Dirección del ganador
        address[] players;          // Lista de participantes
        uint256[] finalScores;      // Puntuaciones finales
        string[] playerAliases;     // Aliases de los jugadores
        bool isFinalized;           // Estado del torneo
    }
    
    // Mapeo de ID a registro de torneo
    mapping(uint256 => TournamentRecord) private tournamentRecords;
    
    // Contador de torneos registrados
    uint256 private recordCounter;
    
    // Eventos para tracking
    event TournamentRegistered(
        uint256 indexed recordId,
        string tournamentName,
        uint256 timestamp,
        address indexed registeredBy
    );
    
    event TournamentFinalized(
        uint256 indexed recordId,
        address indexed champion,
        uint256 timestamp
    );
    
    /**
     * @dev Constructor - inicializa el contador
     */
    constructor() {
        recordCounter = 0;
    }
    
    /**
     * @dev Registra un nuevo torneo en la blockchain
     * @param _name Nombre del torneo
     * @param _players Direcciones de los participantes
     * @param _aliases Aliases de los jugadores
     * @return newRecordId El ID del registro creado
     */
    function registerTournament(
        string memory _name,
        address[] memory _players,
        string[] memory _aliases
    ) public returns (uint256 newRecordId) {
        require(bytes(_name).length > 0, "Tournament name required");
        require(_players.length >= 2, "Minimum 2 players required");
        require(_players.length == _aliases.length, "Players and aliases mismatch");
        
        newRecordId = recordCounter;
        
        TournamentRecord storage newRecord = tournamentRecords[newRecordId];
        newRecord.recordId = newRecordId;
        newRecord.tournamentName = _name;
        newRecord.startTime = block.timestamp;
        newRecord.endTime = 0;
        newRecord.champion = address(0);
        newRecord.players = _players;
        newRecord.finalScores = new uint256[](_players.length);
        newRecord.playerAliases = _aliases;
        newRecord.isFinalized = false;
        
        recordCounter++;
        
        emit TournamentRegistered(newRecordId, _name, block.timestamp, msg.sender);
        
        return newRecordId;
    }
    
    /**
     * @dev Finaliza un torneo y registra los resultados
     * @param _recordId ID del registro del torneo
     * @param _champion Dirección del ganador
     * @param _scores Puntuaciones finales de todos los jugadores
     */
    function finalizeTournament(
        uint256 _recordId,
        address _champion,
        uint256[] memory _scores
    ) public {
        require(_recordId < recordCounter, "Tournament record does not exist");
        
        TournamentRecord storage record = tournamentRecords[_recordId];
        require(!record.isFinalized, "Tournament already finalized");
        require(_scores.length == record.players.length, "Invalid scores array");
        require(_isPlayerInTournament(_champion, record.players), "Champion not in player list");
        
        record.champion = _champion;
        record.finalScores = _scores;
        record.endTime = block.timestamp;
        record.isFinalized = true;
        
        emit TournamentFinalized(_recordId, _champion, block.timestamp);
    }
    
    /**
     * @dev Obtiene información completa de un torneo
     * @param _recordId ID del registro
     * @return recordId ID único del torneo
     * @return tournamentName Nombre del torneo
     * @return startTime Timestamp de inicio
     * @return endTime Timestamp de finalización
     * @return champion Dirección del ganador
     * @return players Lista de participantes
     * @return scores Puntuaciones finales
     * @return aliases Aliases de los jugadores
     * @return isFinalized Estado del torneo
     */
    function getTournamentRecord(uint256 _recordId) public view returns (
        uint256 recordId,
        string memory tournamentName,
        uint256 startTime,
        uint256 endTime,
        address champion,
        address[] memory players,
        uint256[] memory scores,
        string[] memory aliases,
        bool isFinalized
    ) {
        require(_recordId < recordCounter, "Tournament record does not exist");
        
        TournamentRecord memory record = tournamentRecords[_recordId];
        
        return (
            record.recordId,
            record.tournamentName,
            record.startTime,
            record.endTime,
            record.champion,
            record.players,
            record.finalScores,
            record.playerAliases,
            record.isFinalized
        );
    }
    
    /**
     * @dev Obtiene el número total de torneos registrados
     * @return count Total de registros
     */
    function getTotalRecords() public view returns (uint256 count) {
        return recordCounter;
    }
    
    /**
     * @dev Verifica si un jugador participó en un torneo
     * @param _recordId ID del registro
     * @param _player Dirección del jugador
     * @return participated True si el jugador participó
     */
    function isPlayerInTournament(uint256 _recordId, address _player) public view returns (bool participated) {
        require(_recordId < recordCounter, "Tournament record does not exist");
        return _isPlayerInTournament(_player, tournamentRecords[_recordId].players);
    }
    
    /**
     * @dev Obtiene el historial de un jugador específico
     * @param _player Dirección del jugador
     * @return playerHistory Array de IDs de torneos en los que participó
     */
    function getPlayerHistory(address _player) public view returns (uint256[] memory playerHistory) {
        uint256[] memory tempHistory = new uint256[](recordCounter);
        uint256 count = 0;
        
        for (uint256 i = 0; i < recordCounter; i++) {
            if (_isPlayerInTournament(_player, tournamentRecords[i].players)) {
                tempHistory[count] = i;
                count++;
            }
        }
        
        // Crear array del tamaño exacto
        playerHistory = new uint256[](count);
        for (uint256 i = 0; i < count; i++) {
            playerHistory[i] = tempHistory[i];
        }
        
        return playerHistory;
    }
    
    /**
     * @dev Función interna para verificar si una dirección está en el array de jugadores
     * @param _player Dirección a verificar
     * @param _players Array de jugadores
     * @return found True si el jugador está en el array
     */
    function _isPlayerInTournament(address _player, address[] memory _players) private pure returns (bool found) {
        for (uint256 i = 0; i < _players.length; i++) {
            if (_players[i] == _player) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @dev Obtiene estadísticas de victorias de un jugador
     * @param _player Dirección del jugador
     * @return wins Número de torneos ganados
     * @return totalParticipations Total de participaciones
     */
    function getPlayerStats(address _player) public view returns (uint256 wins, uint256 totalParticipations) {
        wins = 0;
        totalParticipations = 0;
        
        for (uint256 i = 0; i < recordCounter; i++) {
            TournamentRecord memory record = tournamentRecords[i];
            if (_isPlayerInTournament(_player, record.players)) {
                totalParticipations++;
                if (record.isFinalized && record.champion == _player) {
                    wins++;
                }
            }
        }
        
        return (wins, totalParticipations);
    }
}
