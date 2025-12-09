import type { Socket } from 'socket.io-client';

export interface User {
  id: number;
  username: string;
  displayName?: string | null;
  email?: string | null;
  avatar?: string;
  wins?: number;
  losses?: number;
  isOnline?: boolean;
  lastSeen?: string | Date;
  provider?: string;
  providerId?: string;
  avatarUrl?: string;
  emailVerified?: boolean;
  sessions?: number;
  host?: boolean;
}

export interface LanguageContent {
  Game: string;
  Profile: string;
  Matches:string;
  Tournaments:string;
  Chat:string;
  FriendRequest: string;
  Settings: string;
  Logout: string;
  Searcher: string;
  localTournament:string;
  localGame: string;
  
  // Notifications
  Notifications: string;
  NotyClearAll: string;
  NotyNoNewNotications: string;
  NotyYoureCaughtUp: string;
  NotyViewAllNotications: string;
  NotyHasSendYouAFriendRequest: string;
  secondsAgo: string;
  minutesAgo: string;
  hoursAgo: string;
  daysAgo: string;
  weeksAgo: string;
  
  grettings: string;
  welcome: string;

  // Login
  loginRegister: string;
  loginUsername: string;
  loginEmailOptional: string;
  loginDisplayNameOptional: string;
  loginPassword: string;
  loginUsernamePlaceholder: string;
  loginEmailPlaceholder: string;
  loginDisplayNamePlaceholder: string;
  loginPasswordPlaceholder: string;
  loginLogin: string;
  loginSignInGoogle: string;
  loginSignIn42: string;
  loginAuthentication: string;
  
  // Profile Section
  profileWelcome: string;
  changeAvatar: string;
  changePassword: string;
  profileUsername: string;
  profileDisplayName: string;
  profilePHDisplayName: string;
  profileEmail: string;
  profilePHEmail: string;
  updateProfile: string;
  profileGameStatistics: string;
  profileWins: string;
  profileLosses: string;
  profileWinRate: string;
  profileFriends: string;
  profilePHenterUsername: string;
  profileAddFriend: string;
  profileNoFriendsYet: string;
  profileIsOnline: string;
  profileIsOffline: string;
  profileMatchHistory: string;
  profileNoMatchesYet: string;
  profileWinMatch: string;
  profileLossMatch: string;
  profileScore: string;
  
  // FriendRequest Section
  frAcceptFriend: string;
  frDeclineFriend: string;
  frNoFriendRequest: string;
  frNoFriendRequestMsg: string;
  frWantsToBeYourFriend: string;
  
  // Matches
  matchesROOMSRUNNING: string;
  matchesNoActiveRooms: string;
  matchesNoActiveRoomsMsg: string;
  matchesNoActiveRoomsAdvice?: string;
  matchesAVAILABLE?: string;
  matchesROOMFULL?: string;
  matchesCannotJoin?: string;
  CannotJoin?: string; // AÑADIDO: también está en el código
  matchesWaiting: string;
  matchesPlayer1: string;
  matchesClickToJoin: string;
  gameWaitingForOpponen?: string; // AÑADIDO: también está en el código
  matchSpeed: string;
  matchRally: string;
  
  // Game
  gamePongGame: string;
  gameOponent?: string; // typo en original
  gameOpponent: string;
  gameStartGame: string;
  gameRoomName: string;
  gameEnterRoomName: string;
  gameSelectDifficulty: string;
  gameEasy: string;
  gameMedium: string;
  gameHard: string;
  gameWaitingForOpponent: string;
  gameGetReadyToPlay: string;
  gameCreateNewRoom: string;
  gameWaiting: string;
  gameAI: string;
  gameHuman: string;
  gameAIDifficultyLevel: string;
  gameEasyEmoji: string;
  gameMediumEmoji: string;
  gameHardEmoji: string;
  gameImpossible: string;
  gameSelectDifficultyBeforeStarting: string;
  gameActive: string;
  gameBack: string;
  gameAIDifficulty: string;
  gameAIOverlayOn: string;
  gameAIOverlayOff: string;
  gameSoundOn: string;
  gameSoundOff: string;
  gameStatsOn: string;
  gameStatsOff: string;
  gamePlayer1: string;
  gamePlayer2: string;
  gameControls: string;
  gameMovePaddle: string;
  gameProTip: string;
  gameMovePaddleForSpin: string;
  gameTopspin: string;
  gameMoveDown: string;
  gameBackspin: string;
  gameMoveUp: string;
  gameVisualEffects: string;
  gameCollisionParticles: string;
  gameOnPaddleHits: string;
  gameSparks: string;
  gameOnWallBounces: string;
  gameWarpEffect: string;
  gameAtExtremeSpeeds: string;
  gameScreenShake: string;
  gameAtHighSpeeds: string;

  // Local Game
  localGamePongGame: string;
  localGamePlayer1: string;
  localGamePlayer2: string;
  localGameStartGame: string;
  localGameWins: string;
  localGameScore: string;
  localGamePlayAgain: string;
  localGameAudioOn: string;
  localGameAudioOff: string;
  localGameStopGame: string;

  // Local Tournament
  localTournamentTitle: string;
  localTournamentDescription: string;
  localTournamentSemifinal: string;
  localTournamentFinal: string;
  localTournamentStartMatch: string;
  localTournamentWins: string;
  localTournamentScore: string;
  localTournamentNextMatch: string;
  localTournamentStartingFinal: string;
  localTournamentChampion: string;
  localTournamentExitTournament: string;
  localTournamentAudioOn: string;
  localTournamentAudioOff: string;
  localTournamentExit: string;
  localTournamentPlayer1: string;
  localTournamentPlayer2: string;
  localTournamentPlayer3: string;
  localTournamentPlayer4: string;
  
  // Settings
  setSelectLanguage: string;
  setCurrentLanguage: string;
  securitySettings:string;
  securityCurrentPassword: string;
  securityCurrentPasswordPlaceholder: string;
  securityNewPassword: string;
  securityNewPasswordPlaceholder: string;
  securityRepeatNewPassword: string;
  securityRepeatNewPasswordPlaceholder: string;
  securityChange: string;

  //Chat

  chatConversations:string;
  chatConversationList:string;
  chatDeleteConversation:string;
  chatNewChat:string;
  chatNewChatFriends:string;
  chatDeleting:string;
  chatNoConversations:string;
  chatLoadingConversations:string;
  chatClose:string;
  chatCreatingNewChat: string;
  chatNoFriendsYet: string;
  chatBlockedUsers:string;
  chatBlockUser:string;
  chatBlocked:string;
  chatUnblock:string;
  chatLoadingBlocked:string;
  chatLoading:string;
  chatBlock:string;
  chatChooseConversation:string;
  chatInvitationToPlayWith:string;
  chatAccept:string;
  chatReject:string;
  chatPlay:string;
  chatNoMessagesYet:string;
  chatYou:string;
  chatMessagePlaceholder:string;
  chatLoadingBlockState:string;
  chatSomeoneBlocked:string;
  chatSend:string;
  chatShowProfileGameStats: string;
  chatShowProfileWins: string;
  chatShowProfileLosses: string;
  chatShowProfileWinRate: string;

  //Tournaments
  tournamentName: string;
  tournamentNumberOfPlayers: string;
  tournamentNumberOfPlayersPlaceholder: string;
  tournamentCreateNewTournament: string;
  tournamentLeaveTournament: string;
  tournamentHost: string;
  tournamentAvailableSeat: string;
  tournamentPlayersLabel: string;
  tournamentNoTournaments: string;
  tournamentCreateTitle: string;
  tournamentTotalLobbies: string;
  tournamentCongratulations: string;
  tournamentYouAreWinner: string;
  tournamentHasWon: string;
  tournamentFinal: string;
  tournamentSemifinals: string;
  tournamentQuarterfinals: string;
  tournamentRoundOf16: string;
  tournamentRoundOf32: string;
  tournamentRoundOf64: string;
  tournamentPlayerBracket: string;
  tournamentNoTournamentFound: string;
  tournamentVS: string;
  tournamentCloseTournament: string;
  tournamentNamePlaceholder:string;
  tournamentScore:string;
  tournamentViewHistory: string;
  tournamentHistory: string;
  tournamentBlockchainHistory: string;
  tournamentCount:string;
  tournamentCounts:string;
  tournamentStoredOnAvalanche: string;
  tournamentSearchPlaceholder: string;
  tournamentAll: string;
  tournamentFinalized: string;
  tournamentPending: string;
  tournamentViewSnowtrace: string;
  tournamentSnowtrace: string;
  tournamentLoadingBlockchain: string;
  tournamentLoadingMessage: string;
  tournamentNoMatchFilters: string;
  tournamentNoRegistered: string;
  tournamentPlayers: string;
  tournamentDate: string;
  tournamentDuration: string;
  tournamentChampion: string;
  tournamentPrevious: string;
  tournamentPaginationStart: string;
  tournamentPaginationMiddle: string;
  tournamentPaginationEnd: string;
  tournamentNext: string;
  tournamentBlockchainRecord: string;
  tournamentRecordId: string;
  tournamentStatus: string;
  tournamentStartTime: string;
  tournamentEndTime: string;
  tournamentMinutes: string;
  tournamentViewOnSnowtrace: string;
  tournamentFinalRankings: string;
  tournamentParticipants: string;
  tournamentPoints: string;
}

export interface AuthContextType {
  user?: User | null;
  setUser?: (user: User | null) => void;
  token?: string | null;
  setToken?: (token: string | null) => void;
  loading?: boolean;
  setLoading?: (loading: boolean) => void;
  language?: Record<string, LanguageContent>;
  lan?: string;
  setLan?: (lan: string) => void;
  login?: (token: string) => void;
  logout?: () => void;
  setLanguage?: (lan: string) => void;
  verifyPassword: (password: string) => number;
  getCsrfToken: () => string;
}

export interface NotificationItem {
  id: number;
  user: string;
  msg: string;
  time: number;
  type: 'friendRequest' | 'gameInvite' | 'system';
  status: boolean;
}
export interface ComponentContextType {
  // Notifications
  notifications?: number;
  setNotifications?: (notifications: number | ((prev: number) => number)) => void;
  notificationsList?: NotificationItem[];
  setNotificationsList?: (list: NotificationItem[] | ((prev: NotificationItem[]) => NotificationItem[])) => void;
  
  // Socket
  socket?: Socket | null;
  
  // Game Rooms
  roomsRunning?: GameRoom[];
  setRoomsRunning?: (rooms: GameRoom[]) => void;
  roomIamIn?: string;
  setRoomIamIn?: (room: string) => void;
  
  // Game State
  isAiEnabled?: boolean;
  setIsAiEnabled?: (enabled: boolean) => void;
  waitingForOpponent?: boolean;
  setWaitingForOpponent?: (waiting: boolean) => void;

  //Chat
  chatMessages: { [conversationId: number]: any[] };
  setChatMessages: React.Dispatch<React.SetStateAction<{ [conversationId: number]: any[] }>>;
  conversations: any[];
  setConversations: React.Dispatch<React.SetStateAction<any[]>>;
  blockedUsers: number[];
  setBlockedUsers: React.Dispatch<React.SetStateAction<number[]>>;
  blockedByUsers: number[];
  setBlockedByUsers: React.Dispatch<React.SetStateAction<number[]>>;
  loadingBlocked: boolean;
}

export interface Friend {
  id?: number;
  username: string;
  displayName?: string;
  isOnline?: boolean;
  status?: string;
  avatar?: string; // AÑADIDO: usado en Profile
}

export interface Match {
  id?: number;
  winner?: string;
  loser?: string;
  date?: string;
  score?: string;
  result?: string;
  opponent?: string;
  // AÑADIDOS: campos usados en Profile
  winnerId?: number;
  Player1?: { username: string };
  Player2?: { username: string };
  player1Score?: number;
  player2Score?: number;
  duration?: number;
  startGameTime?: string;
}

export interface GameRoom {
  roomId: string;
  players: Array<{
    id?: string;
    username?: string;
    isPlayer1: boolean;
    userId?: number;
  }>;
  gameState?: any;
  startTime?: number;
  aiEnabled?: boolean;
  status?: string;
}