import type { ReactNode } from 'react'
import { useContext } from 'react'
import { Navigate } from 'react-router-dom'
import { AuthContext } from '../Context/AuthContext'
import type { AuthContextType } from '../types'

interface ProtectorProps {
  children: ReactNode
}

const ProtectorOfThings = ({ children }: ProtectorProps): React.ReactElement | null => {
  const auth = useContext(AuthContext) as AuthContextType | undefined

  if (!auth) return <Navigate to="/login" />
  const { user, loading } = auth
  if (loading) return <p>...is Loading</p>
  return user ? <>{children}</> : <Navigate to="/login" />
}

export default ProtectorOfThings